#include "optics/Plane.hpp"
#include "optics/OpticObj.hpp"
#include <cmath>

optor::Plane::Plane(const hui::Vector3d& point, const hui::Vector3d& normal)
    : point_{point}, normal_{!normal}
{}

optor::Plane::Plane(const hui::Vector3d& point, const hui::Vector3d& normal, const Material& material)
    : optor::OpticObj(material), point_{point}, normal_{!normal}
{}

std::optional<optor::OpticObj::Intersection> 
optor::Plane::IntersectRay(const hui::Vector3d& rayBegin, const hui::Vector3d& rayDirection) const 
{
    const double denom = normal_ ^ rayDirection;

    if (!denom)
        return std::nullopt;

    const double t = ((point_ - rayBegin) ^ normal_) / denom;

    if (t < 0) 
        return std::nullopt;

    const hui::Vector3d intersectPoint = rayBegin + rayDirection * t;
    const hui::Vector3d intersectNormal = normal_;

    return Intersection{t, intersectPoint, intersectNormal, this};
}

const hui::Vector3d& optor::Plane::GetPoint() const noexcept { return point_; }
const hui::Vector3d& optor::Plane::GetNormal() const noexcept { return normal_; }

void optor::Plane::SetPoint(const hui::Vector3d& point) { point_ = point; }
void optor::Plane::SetNormal(const hui::Vector3d& normal) { normal_ = !normal; }
