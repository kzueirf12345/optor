#include "optics/Light.hpp"
#include "global/Global.hpp"


optor::Light::Light(double radius, const optor::Vector3d& color, double intensity)
    :   optor::Sphere{radius}, color_{optor::color::White}, intensity_(intensity)
{}
optor::Light::Light(double radius, const optor::Vector3d& center, const optor::Vector3d& color, double intensity)
    :   optor::Sphere{radius, center}, color_{optor::color::White}, intensity_(intensity)
{}

optor::Light::Light(double radius, const optor::Vector3d& center, const optor::Material& material, 
                    const optor::Vector3d& color, double intensity)
    :   optor::Sphere{radius, center, material}, color_{optor::color::White}, intensity_(intensity)
{}

const optor::Vector3d& optor::Light::GetColor()     const noexcept { return color_; }
double               optor::Light::GetIntensity() const noexcept { return intensity_; }

void optor::Light::SetColor(const optor::Vector3d& color) { color_ = color; }
void optor::Light::SetIntensity(double intensity)       { intensity_ = intensity; }