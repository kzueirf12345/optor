#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP

#include <optional>

#include "hui/Vector.hpp"
#include "optics/Material.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Sphere: public optor::OpticObj {
    public:
        Sphere(double radius);
        Sphere(double radius, const hui::Vector3d& center);
        Sphere(double radius, const hui::Vector3d& center, const Material& material);
        
        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const hui::Vector3d& rayBegin, const hui::Vector3d& rayDirection) override;


        [[nodiscard]] const hui::Vector3d& GetCenter()  const noexcept;
        [[nodiscard]] double               GetRadius()  const noexcept;
        [[nodiscard]] double               GetRadius2() const noexcept;

        void SetCenter(const hui::Vector3d& center);
        void SetRadius(double radius);

        virtual void Move(const hui::Vector3d& offset) override final;

    protected:
        hui::Vector3d center_;
        double radius_;
        double radius2_;

};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP*/