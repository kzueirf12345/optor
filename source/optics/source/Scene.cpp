#include <cassert>
#include <limits>
#include <optional>

#include "optics/Scene.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/math/color.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "optics/Camera.hpp"
#include "optics/Light.hpp"
#include "optics/OpticObj.hpp"

optor::Scene::Scene(dr4::Window* window, const dr4::Vec2f& size) 
    :   image_{window->CreateImage()},
        size_{size},
        camera_{}, 
        moveDir_{optor::MoveDirection::UNKNOWN},
        maxRecursionDepth_{4},
        bgColor_{optor::color::Blue}
{
    ERROR_HANDLE([this](){
        image_->SetSize(size_);
    });
}

void optor::Scene::Update() {
    if (moveDir_ != optor::MoveDirection::UNKNOWN) {
        ERROR_HANDLE(&optor::Camera::Move, camera_, moveDir_, optor::CAMERA_MOVE_SPEED);
    }

    for (size_t y = 0; y < size_.y; ++y) {
        for (size_t x = 0; x < size_.x; ++x) {
            const size_t pixelIndex = y * size_.x + x;
            
            const optor::Vector2d pixel(x, y);
            const optor::Vector3d rayDirection = ERROR_HANDLE(&optor::Camera::GetRay, camera_, pixel, size_);
            const optor::Vector3d rayOrigin = camera_.GetPosition();
            
            const optor::Vector3d pixelColor = TraceRay(rayOrigin, rayDirection);

            image_->SetPixel(x, y, dr4::Color(pixelColor.x * 255, pixelColor.y * 255, pixelColor.z * 255, 255));
        }
    }

}

optor::Vector3d optor::Scene::TraceRay(const optor::Vector3d& origin, const optor::Vector3d& direction, int depth) const {
    if (depth > maxRecursionDepth_) {
        return bgColor_;
    }
    
    auto closestIntersection = FindClosestIntersection(origin, direction);
    
    if (!closestIntersection) {
        return bgColor_;
    }
    
    return CalculateLighting(closestIntersection.value(), origin, depth);
}

std::optional<optor::OpticObj::Intersection> 
optor::Scene::FindClosestIntersection(const optor::Vector3d& origin, const optor::Vector3d& direction) const 
{
    std::optional<optor::OpticObj::Intersection> closestIntersection;
    double closestDistance = std::numeric_limits<double>::max();
    
    for (const auto& obj : objs_) {
        auto intersection = obj->IntersectRay(origin, direction);
        if (intersection && intersection->distance < closestDistance) {
            closestDistance = intersection->distance;
            closestIntersection = intersection;
        }
    }
    
    return closestIntersection;
}

optor::Vector3d optor::Scene::CalculateLighting(const optor::OpticObj::Intersection& intersection, 
                                              const optor::Vector3d& rayOrigin, int depth) const 
{
    const Material& material = intersection.object->GetMaterial();
    const optor::Vector3d& point = intersection.point;
    const optor::Vector3d& normal = intersection.normal;
    
    optor::Vector3d viewDir = !(rayOrigin - point);
    
    optor::Vector3d result = material.GetDiffuseColor();
    
    for (const Light* light : lights_) {
        optor::Vector3d lightDir = !(light->GetCenter() - point);
        double distanceToLight = (light->GetCenter() - point).Len();
        
        if (IsInShadow(point, lightDir, distanceToLight - 1.1 * light->GetRadius(), intersection.object)) {
            continue;
        }
        
        double diffuseFactor = std::max(0.0, normal ^ lightDir);
        optor::Vector3d diffuse = optor::Product(
            material.GetDiffuseColor() * diffuseFactor, 
            light->GetColor()          * light->GetIntensity()
        );
        
        
        optor::Vector3d reflectDir = Reflect(-lightDir, normal);
        double specularFactor = std::pow(std::max(0.0, reflectDir ^ viewDir), material.GetShininess());
        optor::Vector3d specular = optor::Product(
            material.GetSpecularColor() * specularFactor, 
            light->GetColor()           * light->GetIntensity()
        );
        
        result += diffuse + specular;
    }
    
    const double reflectivity = material.GetReflectivity();
    if (reflectivity > 0) {
        const optor::Vector3d reflectDir = Reflect(-viewDir, normal);
        const optor::Vector3d reflectionColor = TraceRay(point + reflectDir * 0.001, reflectDir, depth + 1);
        result = result * (1 - reflectivity) + reflectionColor * reflectivity;
    }

    const double transparency = material.GetTransparency();
    const double refractivity = material.GetRefractivity();

    if (transparency > 0) {
        const auto refractDir = Refract(-viewDir, normal, refractivity);
        if (refractDir.has_value()) {
            const optor::Vector3d refractedColor = TraceRay(point + refractDir.value() * 0.001, refractDir.value(), depth + 1);
            result = result * (1 - transparency) + refractedColor * transparency;
        }
    }
    
    return result.Clamp({0, 0, 0}, {1, 1, 1});
}

bool optor::Scene::IsInShadow(const optor::Vector3d& point, const optor::Vector3d& lightDir, double lightDistance, const optor::OpticObj* obj) const {
    optor::Vector3d shadowOrigin = point + lightDir * 0.001;
    
    for (const auto& curObj : objs_) {
        auto intersection = curObj->IntersectRay(shadowOrigin, lightDir);
        if (intersection.has_value() && intersection->distance < lightDistance) {
            return true;
        }
    }
    
    return false;
}

optor::Vector3d optor::Scene::Reflect(const optor::Vector3d& incident, const optor::Vector3d& normal) const {
    return incident - normal * 2.0 * (incident ^ normal);
}

std::optional<optor::Vector3d> optor::Scene::Refract(const optor::Vector3d& incident, 
                                                   const optor::Vector3d& normal, 
                                                   double eta) const {
    double cosi = incident ^ normal;
    double etai = 1.0, etat = eta;
    optor::Vector3d n = normal;

    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n = -normal;
    }

    double etaRatio = etai / etat;
    double k = 1.0 - etaRatio * etaRatio * (1.0 - cosi * cosi);

    if (k < 0.0) {
        return std::nullopt;
    }

    return !(incident * etaRatio + n * (etaRatio * cosi - std::sqrt(k)));
}


optor::OpticObj* optor::Scene::AddObj(std::unique_ptr<optor::OpticObj> obj) {
    ERROR_HANDLE([this, &obj](){
        objs_.push_back(std::move(obj));
    });

    optor::OpticObj* const objPtr = objs_.back().get();
    optor::Light*    const lightPtr = dynamic_cast<optor::Light*>(objPtr);

    if (lightPtr) {
        ERROR_HANDLE([this, lightPtr](){
            lights_.push_back(lightPtr);
        });
    }
    return objs_.back().get();
}

const optor::Camera& optor::Scene::GetCamera() const  {
    return camera_;
}
optor::Camera& optor::Scene::GetCamera()        {
    return camera_;
}

void optor::Scene::SetMoveDir(optor::MoveDirection moveDir) {
    moveDir_ = moveDir;
}

optor::OpticObj* optor::Scene::GetObjAtPixel(const optor::Vector2d& pixel) {
    const optor::Vector3d rayDirection = ERROR_HANDLE(&optor::Camera::GetRay, camera_, pixel, size_);
    const optor::Vector3d rayOrigin = camera_.GetPosition();

    auto closestIntersection = FindClosestIntersection(rayOrigin, rayDirection);
    
    if (closestIntersection) {
        return closestIntersection->object;
    }

    return nullptr;
}

optor::MoveDirection optor::Scene::GetMoveDir() const  {
    return moveDir_;
}

const std::vector<std::unique_ptr<optor::OpticObj>>& optor::Scene::GetObjs() const  {
    return objs_;
}

dr4::Image* optor::Scene::GetImage() const {
    return image_.get();
}

optor::Mat4 optor::Scene::LookAt(const optor::Vector3d& eye, const optor::Vector3d& center, const optor::Vector3d& up) {
    optor::Vector3d f = !(center - eye);
    optor::Vector3d s = !(f * up);
    optor::Vector3d u = s * f;

    optor::Mat4 view = {};
    view.m[0][0] = s.x;  view.m[0][1] = u.x;  view.m[0][2] = -f.x; view.m[0][3] = 0;
    view.m[1][0] = s.y;  view.m[1][1] = u.y;  view.m[1][2] = -f.y; view.m[1][3] = 0;
    view.m[2][0] = s.z;  view.m[2][1] = u.z;  view.m[2][2] = -f.z; view.m[2][3] = 0;
    view.m[3][0] = -(s ^ eye);
    view.m[3][1] = -(u ^ eye);
    view.m[3][2] =  (f ^ eye);
    view.m[3][3] = 1;
    return view;
}

optor::Mat4 optor::Scene::Perspective(double fovDeg, double aspect, double near, double far) {
    double fovRad = fovDeg * M_PI / 180.0;
    double f = 1.0 / std::tan(fovRad / 2.0);
    Mat4 p = {};
    p.m[0][0] = f / aspect;
    p.m[1][1] = f;
    p.m[2][2] = (far + near) / (near - far);
    p.m[2][3] = -1.0;
    p.m[3][2] = (2 * far * near) / (near - far);
    return p;
}

optor::ScreenPoint optor::Scene::ProjectPoint(const optor::Vector3d& p, const Mat4& view, const Mat4& proj,
                         const dr4::Vec2f& screenSize)
{
    // в clip space
    double x = p.x * view.m[0][0] + p.y * view.m[1][0] + p.z * view.m[2][0] + view.m[3][0];
    double y = p.x * view.m[0][1] + p.y * view.m[1][1] + p.z * view.m[2][1] + view.m[3][1];
    double z = p.x * view.m[0][2] + p.y * view.m[1][2] + p.z * view.m[2][2] + view.m[3][2];
    double w = p.x * view.m[0][3] + p.y * view.m[1][3] + p.z * view.m[2][3] + view.m[3][3];

    double cx = x * proj.m[0][0] + y * proj.m[1][0] + z * proj.m[2][0] + w * proj.m[3][0];
    double cy = x * proj.m[0][1] + y * proj.m[1][1] + z * proj.m[2][1] + w * proj.m[3][1];
    double cz = x * proj.m[0][2] + y * proj.m[1][2] + z * proj.m[2][2] + w * proj.m[3][2];
    double cw = x * proj.m[0][3] + y * proj.m[1][3] + z * proj.m[2][3] + w * proj.m[3][3];

    if (cw <= 0.0)  // за камерой
        return {0, 0, false};

    // нормализуем
    cx /= cw;
    cy /= cw;

    // из [-1, 1] в [0, screenSize]
    double sx = (cx * 0.5 + 0.5) * screenSize.x;
    double sy = (1.0 - (cy * 0.5 + 0.5)) * screenSize.y;

    return {sx, sy, true};
}

std::optional<std::array<dr4::Vec2f, 4>> optor::Scene::ProjectAABBToScreen(
    const std::array<optor::Vector3d, 8>& aabb,
    const optor::Camera& camera,
    const dr4::Vec2f& screenSize)
{
    Mat4 view = LookAt(camera.GetPosition(), 
                       camera.GetPosition() + camera.GetFront(),
                       camera.GetUp());

    Mat4 proj = Perspective(camera.GetFov(), screenSize.x / screenSize.y, 0.1, 1000.0);

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    bool anyVisible = false;

    for (auto& v : aabb) {
        auto sp = ProjectPoint(v, view, proj, screenSize);
        if (!sp.visible)
            continue;
        anyVisible = true;
        minX = std::min(minX, sp.x);
        minY = std::min(minY, sp.y);
        maxX = std::max(maxX, sp.x);
        maxY = std::max(maxY, sp.y);
    }

    if (!anyVisible)
    {
        return std::nullopt;
    }

    std::cerr << "kek\n";

    return std::array<dr4::Vec2f, 4>{
        dr4::Vec2f(minX, minY),
        dr4::Vec2f(maxX, minY),
        dr4::Vec2f(maxX, maxY),
        dr4::Vec2f(minX, maxY)
    };
}
