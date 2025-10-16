#include "optics/Light.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Color.hpp"
#include "optics/Sphere.hpp"
#include "global/Global.hpp"

optor::Light::Light(double radius) 
    :   optor::Light(radius, {0, 0, 0})
{}
optor::Light::Light(double radius, const hui::Vector3d& center) 
    :   optor::Sphere{radius, center},
        emmitColor_{optor::color::White.GetNormalized()}
{}

std::optional<hui::Color> optor::Light::TraceRay(const hui::Vector3d& rayDir,
                                                 const hui::Vector3d& cameraPos, 
                                                 const std::vector<optor::Light*>& lights) const {
    if (!ERROR_HANDLE(&optor::Sphere::IntersectRay, this, cameraPos, rayDir)) {
        return std::nullopt;
    }
    
    return emmitColor_;
}

hui::Color optor::Light::GetEmmitColor() const noexcept {
    return emmitColor_;
}

void optor::Light::SetEmmitColor(const hui::Color& color) {
    emmitColor_ = color;
}