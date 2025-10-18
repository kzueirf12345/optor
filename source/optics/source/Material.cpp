#include "optics/Material.hpp"
#include "global/Global.hpp"

optor::Material::Material() 
    :   ambient_{optor::color::Poison.GetNormalized()},
        diffuse_{optor::color::Poison.GetNormalized()},
        specular_{optor::color::Poison.GetNormalized()},
        shininess_{32},
        reflectivity_{0},
        refractivity_{0},
        transparency_{0}
{}

optor::Material::Material(const hui::Vector3d& ambient, const hui::Vector3d& diffuse, 
                          const hui::Vector3d& specular, double shininess)
    :   ambient_{ambient},
        diffuse_{diffuse},
        specular_{specular},
        shininess_{shininess},
        reflectivity_{0},
        refractivity_{0},
        transparency_{0}

{}

hui::Vector3d optor::Material::GetAmbientColor() const noexcept { return ambient_; }
hui::Vector3d optor::Material::GetDiffuseColor() const noexcept { return diffuse_; }
hui::Vector3d optor::Material::GetSpecularColor()const noexcept { return specular_; }
double        optor::Material::GetShininess()    const noexcept { return shininess_; }
double        optor::Material::GetReflectivity() const noexcept { return reflectivity_; }
double        optor::Material::GetTransparency() const noexcept { return transparency_; }
double        optor::Material::GetRefractivity() const noexcept { return refractivity_; }

void optor::Material::SetAmbientColor (const hui::Vector3d& color) { ambient_ = color; }
void optor::Material::SetDiffuseColor (const hui::Vector3d& color) { diffuse_ = color; }
void optor::Material::SetSpecularColor(const hui::Vector3d& color) { specular_ = color; }
void optor::Material::SetShininess    (double shininess)           { shininess_ = shininess; }
void optor::Material::SetReflectivity (double reflectivity)        { reflectivity_ = reflectivity; }
void optor::Material::SetTransparency (double transparency)        { transparency_ = transparency; }
void optor::Material::SetRefractivity (double refractivity)        { refractivity_ = refractivity; }