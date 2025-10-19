#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLE_HPP

#include <optional>
#include "hui/Vector.hpp"
#include "optics/OpticObj.hpp"

namespace optor {

class Triangle : public OpticObj {
public:
    Triangle(const hui::Vector3d& v0, const hui::Vector3d& v1, const hui::Vector3d& v2);

    [[nodiscard]] std::optional<Intersection> 
    IntersectRay(const hui::Vector3d& rayOrigin, const hui::Vector3d& rayDir) const override;

    [[nodiscard]] const hui::Vector3d& GetNormal() const noexcept;

private:
    hui::Vector3d v0_, v1_, v2_;
    hui::Vector3d normal_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLE_HPP*/
