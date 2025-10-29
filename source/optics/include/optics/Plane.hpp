#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_PLANE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_PLANE_HPP

#include <optional>
#include "hui/Vector.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Plane : public OpticObj {
    public:
        Plane(const hui::Vector3d& point, const hui::Vector3d& normal);
        Plane(const hui::Vector3d& point, const hui::Vector3d& normal, const Material& material);

        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const hui::Vector3d& rayBegin, const hui::Vector3d& rayDirection) override;

        [[nodiscard]] const hui::Vector3d& GetPoint()  const noexcept;
        [[nodiscard]] const hui::Vector3d& GetNormal() const noexcept;

        void SetPoint(const hui::Vector3d& point);
        void SetNormal(const hui::Vector3d& normal);

    protected:
        hui::Vector3d point_;
        hui::Vector3d normal_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_PLANE_HPP*/
