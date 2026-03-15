#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_MATERIAL_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_MATERIAL_HPP

#include "optics/Vector.hpp"

namespace optor 
{

class Material {
    public:
        Material();
        Material(const optor::Vector3d& ambient, const optor::Vector3d& diffuse, 
                 const optor::Vector3d& specular, double shininess, double reflectivity, 
                 double refractivity, double transparency);

        [[nodiscard]] optor::Vector3d GetAmbientColor() const noexcept;
        [[nodiscard]] optor::Vector3d GetDiffuseColor() const noexcept;
        [[nodiscard]] optor::Vector3d GetSpecularColor()const noexcept;
        [[nodiscard]] double          GetShininess()    const noexcept;
        [[nodiscard]] double          GetReflectivity() const noexcept;
        [[nodiscard]] double          GetTransparency() const noexcept;
        [[nodiscard]] double          GetRefractivity() const noexcept;

        void SetAmbientColor(const optor::Vector3d& color);
        void SetAmbientColorX(double color0);
        void SetAmbientColorY(double color1);
        void SetAmbientColorZ(double color2);

        void SetDiffuseColor(const optor::Vector3d& color);
        void SetDiffuseColorX(double color0);
        void SetDiffuseColorY(double color1);
        void SetDiffuseColorZ(double color2);

        void SetSpecularColor(const optor::Vector3d& color);
        void SetSpecularColorX(double color0);
        void SetSpecularColorY(double color1);
        void SetSpecularColorZ(double color2);

        void SetShininess(double shininess);
        void SetReflectivity(double reflectivity);
        void SetTransparency(double transparency);
        void SetRefractivity(double refractivity);

    private:
        optor::Vector3d ambient_;  
        optor::Vector3d diffuse_;    
        optor::Vector3d specular_;  
        double shininess_;           
        double reflectivity_;
        double refractivity_;
        double transparency_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_MATERIAL_HPP*/