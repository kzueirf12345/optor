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

void optor::Light::WriteSerialize(FILE* file, size_t baseTabCnt) const  {
    std::string baseIndent(baseTabCnt, ' ');
    std::string innerIndent(baseTabCnt + 4, ' ');
    
    fprintf(file, "%s{\n", baseIndent.c_str());
    
    fprintf(file, "%s\"type\": \"%s\",\n", innerIndent.c_str(), GetTypeName().c_str());
    
    OpticObj::WriteSerialize(file, baseTabCnt + 4);
    
    fprintf(file, "%s\"center\": [%g, %g, %g],\n", 
            innerIndent.c_str(), center_.x, center_.y, center_.z);
    
    fprintf(file, "%s\"radius\": %g,\n", innerIndent.c_str(), radius_);
    
    fprintf(file, "%s\"color\": [%g, %g, %g],\n", 
            innerIndent.c_str(), color_.x, color_.y, color_.z);
    
    fprintf(file, "%s\"intensity\": %g\n", innerIndent.c_str(), intensity_);
    
    fprintf(file, "%s}", baseIndent.c_str());
}