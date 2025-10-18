#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_MATERIAL_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_MATERIAL_HPP

#include "hui/Vector.hpp"

namespace optor 
{

class Material {
    public:
        Material();
        Material(const hui::Vector3d& ambient, const hui::Vector3d& diffuse, 
                 const hui::Vector3d& specular, double shininess);

        [[nodiscard]] hui::Vector3d GetAmbientColor() const noexcept;
        [[nodiscard]] hui::Vector3d GetDiffuseColor() const noexcept;
        [[nodiscard]] hui::Vector3d GetSpecularColor()const noexcept;
        [[nodiscard]] double        GetShininess()    const noexcept;
        [[nodiscard]] double        GetReflectivity() const noexcept;
        [[nodiscard]] double        GetTransparency() const noexcept;
        [[nodiscard]] double        GetRefractivity() const noexcept;

        void SetAmbientColor (const hui::Vector3d& color);
        void SetDiffuseColor (const hui::Vector3d& color);
        void SetSpecularColor(const hui::Vector3d& color);
        void SetShininess    (double shininess);
        void SetReflectivity (double reflectivity);
        void SetTransparency (double transparency);
        void SetRefractivity (double refractivity);

    private:
        hui::Vector3d ambient_;  
        hui::Vector3d diffuse_;    
        hui::Vector3d specular_;  
        double shininess_;           
        double reflectivity_;
        double refractivity_;
        double transparency_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_MATERIAL_HPP*/