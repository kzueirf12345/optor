#include "optics/Material.hpp"

optor::Material::Material() 
    :   ambient_{},
        diffuse_{},
        specular_{},
        shininess_{32},
        reflectivity_{0},
        refractivity_{0},
        transparency_{0}
{}

optor::Material::Material(const optor::Vector3d& ambient, const optor::Vector3d& diffuse, 
                          const optor::Vector3d& specular, double shininess, double reflectivity, 
                          double refractivity, double transparency)
    :   ambient_{ambient},
        diffuse_{diffuse},
        specular_{specular},
        shininess_{shininess},
        reflectivity_{reflectivity},
        refractivity_{refractivity},
        transparency_{transparency}
{}

optor::Vector3d optor::Material::GetAmbientColor() const noexcept { return ambient_; }
optor::Vector3d optor::Material::GetDiffuseColor() const noexcept { return diffuse_; }
optor::Vector3d optor::Material::GetSpecularColor()const noexcept { return specular_; }
double        optor::Material::GetShininess()    const noexcept   { return shininess_; }
double        optor::Material::GetReflectivity() const noexcept   { return reflectivity_; }
double        optor::Material::GetTransparency() const noexcept   { return transparency_; }
double        optor::Material::GetRefractivity() const noexcept   { return refractivity_; }

void optor::Material::SetAmbientColor(const optor::Vector3d& color) { ambient_ = color; }

void optor::Material::SetAmbientColorX(double color0) { ambient_.x = color0; }
void optor::Material::SetAmbientColorY(double color1) { ambient_.y = color1; }
void optor::Material::SetAmbientColorZ(double color2) { ambient_.z = color2; }

void optor::Material::SetDiffuseColor(const optor::Vector3d& color) { diffuse_ = color; }

void optor::Material::SetDiffuseColorX(double color0) { diffuse_.x = color0; }
void optor::Material::SetDiffuseColorY(double color1) { diffuse_.y = color1; }
void optor::Material::SetDiffuseColorZ(double color2) { diffuse_.z = color2; }

void optor::Material::SetSpecularColor(const optor::Vector3d& color) { specular_ = color; }

void optor::Material::SetSpecularColorX(double color0) { specular_.x = color0; }
void optor::Material::SetSpecularColorY(double color1) { specular_.y = color1; }
void optor::Material::SetSpecularColorZ(double color2) { specular_.z = color2; }

void optor::Material::SetShininess(double shininess) { shininess_ = shininess; }
void optor::Material::SetReflectivity(double reflectivity) { reflectivity_ = reflectivity; }
void optor::Material::SetTransparency(double transparency) { transparency_ = transparency; }
void optor::Material::SetRefractivity(double refractivity) { refractivity_ = refractivity; }