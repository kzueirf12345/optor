#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_PLANE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_PLANE_HPP

#include <optional>

#include "optics/Vector.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Plane : public OpticObj {
    public:
        Plane(const optor::Vector3d& point, const optor::Vector3d& normal);
        Plane(const optor::Vector3d& point, const optor::Vector3d& normal, const Material& material);

        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const optor::Vector3d& rayBegin, const optor::Vector3d& rayDirection) override;

        [[nodiscard]] const optor::Vector3d& GetPoint()  const noexcept;
        [[nodiscard]] const optor::Vector3d& GetNormal() const noexcept;

        void SetPoint(const optor::Vector3d& point);
        void SetNormal(const optor::Vector3d& normal);

        virtual void Move(const optor::Vector3d& offset) override final;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "Plane"; };

    protected:
        optor::Vector3d point_;
        optor::Vector3d normal_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_PLANE_HPP*/
