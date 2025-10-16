#include <cassert>
#include <limits>

#include "optics/Scene.hpp"
#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "hui/TexturedShape.hpp"
#include "hui/Vector.hpp"
#include "optics/Camera.hpp"
#include "optics/OpticObj.hpp"
#include "hui/Color.hpp"

optor::Scene::Scene(const hui::Vector2d& boxSize) 
    : optor::Scene(boxSize, {0, 0})
{}

optor::Scene::Scene(const hui::Vector2d& boxSize, const hui::Vector2d& position) 
    : hui::Textured(boxSize, position), camera_{}
{
    for (size_t y = 0; y < boxSize_.y; ++y) {
        for (size_t x = 0; x < boxSize_.x; ++x) {
            pixelBuffer_[y * boxSize_.x + x] = optor::color::Transparent.GetInt();
        }
    }
}

void optor::Scene::Update() {
    for (size_t y = 0; y < boxSize_.y; ++y) {
        for (size_t x = 0; x < boxSize_.x; ++x) {
            const size_t pixelIndex = y * boxSize_.x + x;

            const hui::Vector3d rayDir = ERROR_HANDLE(
                &optor::Camera::GetRay, 
                camera_, 
                hui::Vector2d(x, y), 
                boxSize_
            );

            pixelBuffer_[pixelIndex] = optor::color::Transparent.GetInt();

            double minDist = std::numeric_limits<double>::max();

            for (auto& obj : objs_) {
                double curDist = 0;
                const std::optional<hui::Color> color = 
                    ERROR_HANDLE(&optor::Scene::TraceRay, this, rayDir, obj.get(), &curDist);

                if (color.has_value() && curDist < minDist)
                {
                    pixelBuffer_[pixelIndex] = color.value().GetInt();
                    minDist = curDist;
                }
            }

        }
    }

    ERROR_HANDLE([this](){
        hui::Textured::Update();
    });
}

std::optional<hui::Color> optor::Scene::TraceRay(const hui::Vector3d rayDir, const optor::OpticObj* obj,
                                                 double* dist) {
    assert(obj);
    assert(dist);

    const hui::Vector3d cameraPos = camera_.GetPosition();

    std::optional<double> distCamera2Intersect = ERROR_HANDLE(
        &optor::OpticObj::IntersectRay, 
        obj, 
        cameraPos, 
        rayDir
    );
    
    if (!distCamera2Intersect.has_value()) {
        return std::nullopt;
    }

    *dist = distCamera2Intersect.value(); 
    
    const hui::Vector3d intersectPoint = cameraPos + rayDir * *dist;
    const hui::Vector3d normalVec = obj->GetNormal(intersectPoint);
    
    const hui::Vector3d ambientColor = obj->GetAmbientColor().GetNormalized();
    const hui::Vector3d diffColor    = obj->GetDiffColor().GetNormalized();
    const hui::Vector3d specColor    = obj->GetSpecColor().GetNormalized();
    
    const hui::Vector3d ambientPart = ambientColor * GLOBAL_AMBIENT_COEF;
    
    hui::Vector3d diffPart(0, 0, 0);
    hui::Vector3d specPart(0, 0, 0);
    
    for (const auto& light : lights_) {
        const hui::Vector3d lightCenter = light->GetCenter();
        const hui::Vector3d lightDir = !(lightCenter - intersectPoint);
        
        if (ERROR_HANDLE(&optor::Scene::IsEclipse, this, obj, light, intersectPoint)) {
            continue;
        }

        const hui::Vector3d curEmmitColor = light->GetEmmitColor().GetNormalized();
        
        const double        curDiffCoef = std::max(0., lightDir ^ normalVec); 
        const hui::Vector3d curDiffPart = hui::Product(diffColor, curEmmitColor);
        diffPart += curDiffCoef * curDiffPart;
        
        const hui::Vector3d reflectDir = !(hui::Reflect(lightDir, normalVec));
        const double specAngle = std::max(0., reflectDir ^ (rayDir));
        
        const double curSpecCoef = std::pow(specAngle, obj->GetShininess());
        
        const hui::Vector3d curSpecPart = hui::Product(specColor, curEmmitColor);
        specPart += curSpecCoef * curSpecPart;
    }

    const hui::Vector3d resultColor(ambientPart + diffPart + specPart);

    return hui::Color(resultColor.Clump({0, 0, 0}, {1, 1, 1}));
}

bool optor::Scene::IsEclipse(const optor::OpticObj* obj, const optor::Light* light, 
                             const hui::Vector3d& intersectPoint) {
    assert(obj);
    assert(light);

    const hui::Vector3d lightCenter = light->GetCenter();
    const hui::Vector3d lightDir = !(lightCenter - intersectPoint);
    
    const double distLight2Intersect = (lightCenter - intersectPoint).Len();

    bool isEclipse = false;
    for (const auto& otherObj : objs_) {
        if (otherObj.get() == obj || light == otherObj.get()) {
            continue;
        }
        const std::optional<double> distLight2Other = 
            ERROR_HANDLE(&optor::OpticObj::IntersectRay, otherObj, lightCenter, -lightDir);

        if (distLight2Other.has_value() && distLight2Other.value() < distLight2Intersect) {
            isEclipse = true;
            break;
        }
    }
    
    return isEclipse;
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