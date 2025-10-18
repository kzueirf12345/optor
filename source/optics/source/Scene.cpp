#include <cassert>
#include <limits>

#include "optics/Scene.hpp"
#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "hui/TexturedShape.hpp"
#include "hui/Vector.hpp"
#include "optics/Camera.hpp"
#include "optics/Light.hpp"
#include "optics/OpticObj.hpp"
#include "hui/Color.hpp"

optor::Scene::Scene(const hui::Vector2d& boxSize) 
    : optor::Scene(boxSize, {0, 0})
{}

optor::Scene::Scene(const hui::Vector2d& boxSize, const hui::Vector2d& position) 
    :   hui::Textured(boxSize, position), 
        camera_{}, 
        moveDir_{optor::MoveDirection::UNKNOWN},
        maxRecursionDepth_{4},
        bgColor_{optor::color::Blue.GetNormalized()}
{}

void optor::Scene::Update() {
    if (moveDir_ != optor::MoveDirection::UNKNOWN) {
        ERROR_HANDLE(&optor::Camera::Move, camera_, moveDir_, optor::CAMERA_MOVE_SPEED);
    }

    for (size_t y = 0; y < boxSize_.y; ++y) {
        for (size_t x = 0; x < boxSize_.x; ++x) {
            const size_t pixelIndex = y * boxSize_.x + x;
            
            const hui::Vector2d pixel(x, y);
            const hui::Vector3d rayDirection = ERROR_HANDLE(&optor::Camera::GetRay, camera_, pixel, boxSize_);
            const hui::Vector3d rayOrigin = camera_.GetPosition();
            
            const hui::Vector3d pixelColor = TraceRay(rayOrigin, rayDirection);

            pixelBuffer_[pixelIndex] = hui::Color(pixelColor).GetABGR();

        }
    }

    ERROR_HANDLE([this](){
        hui::Textured::Update();
    });
}

hui::Vector3d optor::Scene::TraceRay(const hui::Vector3d& origin, const hui::Vector3d& direction, int depth) const {
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
optor::Scene::FindClosestIntersection(const hui::Vector3d& origin, const hui::Vector3d& direction) const 
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

hui::Vector3d optor::Scene::CalculateLighting(const optor::OpticObj::Intersection& intersection, 
                                              const hui::Vector3d& rayOrigin, int depth) const 
{
    const Material& material = intersection.object->GetMaterial();
    const hui::Vector3d& point = intersection.point;
    const hui::Vector3d& normal = intersection.normal;
    
    hui::Vector3d viewDir = !(rayOrigin - point);
    
    hui::Vector3d result = material.GetAmbientColor();
    
    for (const Light* light : lights_) {
        hui::Vector3d lightDir = !(light->GetCenter() - point);
        double distanceToLight = (light->GetCenter() - point).Len();
        
        if (IsInShadow(point, lightDir, distanceToLight - 1.1 * light->GetRadius(), intersection.object)) {
            continue;
        }
        
        double diffuseFactor = std::max(0.0, normal ^ lightDir);
        hui::Vector3d diffuse = hui::Product(
            material.GetDiffuseColor() * diffuseFactor, 
            light->GetColor()          * light->GetIntensity()
        );
        
        
        hui::Vector3d reflectDir = Reflect(-lightDir, normal);
        double specularFactor = std::pow(std::max(0.0, reflectDir ^ viewDir), material.GetShininess());
        hui::Vector3d specular = hui::Product(
            material.GetSpecularColor() * specularFactor, 
            light->GetColor()           * light->GetIntensity()
        );
        
        result += diffuse + specular;
    }
    
    //
    // if (material.GetReflection() > 0.0) {
    //     hui::Vector3d reflectDir = Reflect(-viewDir, normal);
    //     hui::Color reflectionColor = TraceRay(point + reflectDir * 0.001, reflectDir, depth + 1);
    //     result = result * (1 - material.GetReflection()) + reflectionColor * material.GetReflection();
    // }
    
    return result.Clamp({0, 0, 0}, {1, 1, 1});
}

bool optor::Scene::IsInShadow(const hui::Vector3d& point, const hui::Vector3d& lightDir, double lightDistance, const optor::OpticObj* obj) const {
    hui::Vector3d shadowOrigin = point + lightDir * 0.001;
    
    
    for (const auto& curObj : objs_) {
        auto intersection = curObj->IntersectRay(shadowOrigin, lightDir);
        if (intersection.has_value() && intersection->distance < lightDistance) {
            return true;
        }
    }
    
    return false;
}

hui::Vector3d optor::Scene::Reflect(const hui::Vector3d& incident, const hui::Vector3d& normal) const {
    return incident - normal * 2.0 * (incident ^ normal);
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

const optor::Camera& optor::Scene::GetCamera() const noexcept {
    return camera_;
}
optor::Camera& optor::Scene::GetCamera()       noexcept {
    return camera_;
}

void optor::Scene::SetMoveDir(optor::MoveDirection moveDir) {
    moveDir_ = moveDir;
}

optor::MoveDirection optor::Scene::GetMoveDir() const noexcept {
    return moveDir_;
}