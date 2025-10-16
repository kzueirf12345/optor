#include "optics/Scene.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/TexturedShape.hpp"
#include "hui/Vector.hpp"
#include "optics/OpticObj.hpp"

optor::Scene::Scene(const hui::Vector2d& boxSize) 
    : optor::Scene(boxSize, {0, 0})
{}

optor::Scene::Scene(const hui::Vector2d& boxSize, const hui::Vector2d& position) 
    : hui::TexturedShape(boxSize, position)
{}

void optor::Scene::Update() {
    for (size_t y = 0; y < boxSize_.y; ++y) {
        for (size_t x = 0; x < boxSize_.x; ++x) {
            const size_t pixelIndex = y * boxSize_.x + x;

            double normalizedX = (x + 0.5) / boxSize_.x;
            double normalizedY = (y + 0.5) / boxSize_.y;

            normalizedX = (2 * normalizedX - 1);
            normalizedY = (1 - 2 * normalizedY);

            constexpr double FOV = 60;
            
            const double fovTan = std::tan(FOV * M_PI / 360); // tan(fov/2)
            const double ratioAspect = boxSize_.y * 1. / boxSize_.x;
            
            normalizedX *= fovTan * ratioAspect;
            normalizedY *= fovTan;
            hui::Vector3d rayDir(normalizedX, normalizedY, -1);
            rayDir = !rayDir;
            
            for (auto& obj : objs_) { // FIXME check перекрывание
                pixelBuffer_[pixelIndex] =  ERROR_HANDLE(&optor::OpticObj::TraceRay, obj, hui::Vector3d(0, 0, 0), rayDir);
            }
        }
    }

    ERROR_HANDLE([this](){
        hui::TexturedShape::Update();
    });
}

optor::OpticObj* optor::Scene::AddObj(std::unique_ptr<optor::OpticObj> obj) {
    ERROR_HANDLE([this, &obj](){
        objs_.push_back(std::move(obj));
    });
    return objs_.back().get();
}