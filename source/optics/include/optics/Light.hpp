#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP

#include "optics/Vector.hpp"
#include "optics/Material.hpp"
#include "optics/Sphere.hpp"

namespace optor 
{

class Light : public Sphere {
    public:
        Light(double radius, const optor::Vector3d& color, double intensity = 1.0);
        Light(double radius, const optor::Vector3d& center, const optor::Vector3d& color, 
              double intensity = 1.0);
        Light(double radius, const optor::Vector3d& center, const Material& material, 
              const optor::Vector3d& color, double intensity = 1.0);

        [[nodiscard]] const optor::Vector3d& GetColor()     const noexcept;
        [[nodiscard]] double               GetIntensity() const noexcept;

        void SetColor(const optor::Vector3d& color);
        void SetIntensity(double intensity);

    private:
        optor::Vector3d color_;
        double intensity_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_LIGHT_HPP*/