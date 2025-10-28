#include "optics/Light.hpp"
#include "global/Global.hpp"


optor::Light::Light(double radius, const hui::Vector3d& color, double intensity)
    :   optor::Sphere{radius}, color_{optor::color::White.GetNormalized()}, intensity_(intensity)
{}
optor::Light::Light(double radius, const hui::Vector3d& center, const hui::Vector3d& color, double intensity)
    :   optor::Sphere{radius, center}, color_{optor::color::White.GetNormalized()}, intensity_(intensity)
{}

optor::Light::Light(double radius, const hui::Vector3d& center, const optor::Material& material, 
                    const hui::Vector3d& color, double intensity)
    :   optor::Sphere{radius, center, material}, color_{optor::color::White.GetNormalized()}, intensity_(intensity)
{}

const hui::Vector3d& optor::Light::GetColor()     const noexcept { return color_; }
double               optor::Light::GetIntensity() const noexcept { return intensity_; }

void optor::Light::SetColor(const hui::Vector3d& color) { color_ = color; }
void optor::Light::SetIntensity(double intensity)       { intensity_ = intensity; }