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

            for (auto& obj : objs_) { // FIXME check перекрывание
                const std::optional<hui::Color> color = ERROR_HANDLE(
                    &optor::OpticObj::TraceRay, 
                    obj, 
                    rayDir,
                    camera_.GetPosition(), 
                    lights_
                );
                if (color.has_value() && pixelBuffer_[pixelIndex] == optor::color::Transparent.GetInt())
                {
                    pixelBuffer_[pixelIndex] =  color.value().GetInt();
                }
            }

        }
    }

    ERROR_HANDLE([this](){
        hui::Textured::Update();
    });
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