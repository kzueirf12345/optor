#include "optics/Light.hpp"
#include "hui/Color.hpp"
#include "optics/Sphere.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::Light::Light(double radius) 
    :   optor::Light(radius, {0, 0, 0})
{}
optor::Light::Light(double radius, const hui::Vector3d& center) 
    :   optor::Sphere{radius, center},
        emmitColor_{optor::color::White.GetNormalized()}
{
    ERROR_HANDLE(&optor::Light::SetAmbientColor, this, emmitColor_);
}

hui::Color optor::Light::GetEmmitColor() const noexcept {
    return emmitColor_;
}

void optor::Light::SetEmmitColor(const hui::Color& color) {
    emmitColor_ = color;
}