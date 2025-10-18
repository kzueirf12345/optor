#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP

#include "hui/Vector.hpp"
#include "optics/Sphere.hpp"

namespace optor 
{

class Light : public Sphere {
    public:
        Light(double radius,                              const hui::Vector3d& color, double intensity = 1.0);
        Light(double radius, const hui::Vector3d& center, const hui::Vector3d& color, double intensity = 1.0);

        [[nodiscard]] const hui::Vector3d& GetColor()     const noexcept;
        [[nodiscard]] double               GetIntensity() const noexcept;

        void SetColor(const hui::Vector3d& color);
        void SetIntensity(double intensity);

    private:
        hui::Vector3d color_;
        double intensity_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP*/