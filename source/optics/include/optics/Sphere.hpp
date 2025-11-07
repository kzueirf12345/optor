#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP

#include <optional>

#include "optics/Vector.hpp"
#include "optics/Material.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Sphere: public optor::OpticObj {
    public:
        Sphere(double radius);
        Sphere(double radius, const optor::Vector3d& center);
        Sphere(double radius, const optor::Vector3d& center, const Material& material);
        
        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const optor::Vector3d& rayBegin, const optor::Vector3d& rayDirection) override;


        [[nodiscard]] const optor::Vector3d& GetCenter()  const noexcept;
        [[nodiscard]] double               GetRadius()  const noexcept;
        [[nodiscard]] double               GetRadius2() const noexcept;

        void SetCenter(const optor::Vector3d& center);
        void SetRadius(double radius);

        virtual void Move(const optor::Vector3d& offset) override final;

        std::array<optor::Vector3d, 8> GetAABB() const override;
        virtual optor::Vector3d GetCoord() const override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "Sphere"; };

    protected:
        optor::Vector3d center_;
        double radius_;
        double radius2_;

};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP*/