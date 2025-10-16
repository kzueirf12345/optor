#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP

#include "hui/Vector.hpp"
#include "optics/Sphere.hpp"

namespace optor 
{

class Light: public Sphere {
    public:
        Light(double radius);
        Light(double radius, const hui::Vector3d& center);

        [[nodiscard]] hui::Color GetEmmitColor() const noexcept;

        void SetEmmitColor(const hui::Color& color);
        
    protected:
        hui::Color emmitColor_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP*/