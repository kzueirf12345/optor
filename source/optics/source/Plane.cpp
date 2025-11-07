#include "optics/Plane.hpp"
#include "optics/OpticObj.hpp"
#include <cmath>

optor::Plane::Plane(const optor::Vector3d& point, const optor::Vector3d& normal)
    : point_{point}, normal_{!normal}
{}

optor::Plane::Plane(const optor::Vector3d& point, const optor::Vector3d& normal, const Material& material)
    : optor::OpticObj(material), point_{point}, normal_{!normal}
{}

std::optional<optor::OpticObj::Intersection> 
optor::Plane::IntersectRay(const optor::Vector3d& rayBegin, const optor::Vector3d& rayDirection)
{
    const double denom = normal_ ^ rayDirection;

    if (!denom)
        return std::nullopt;

    const double t = ((point_ - rayBegin) ^ normal_) / denom;

    if (t < 0) 
        return std::nullopt;

    const optor::Vector3d intersectPoint = rayBegin + rayDirection * t;
    const optor::Vector3d intersectNormal = normal_;

    return Intersection{t, intersectPoint, intersectNormal, this};
}

const optor::Vector3d& optor::Plane::GetPoint() const noexcept { return point_; }
const optor::Vector3d& optor::Plane::GetNormal() const noexcept { return normal_; }

void optor::Plane::SetPoint(const optor::Vector3d& point) { point_ = point; }
void optor::Plane::SetNormal(const optor::Vector3d& normal) { normal_ = !normal; }

void optor::Plane::Move(const optor::Vector3d& offset) {
    point_ += offset;
}

std::array<optor::Vector3d, 8> optor::Plane::GetAABB() const {
    return {
        point_ + optor::Vector3d{-INFINITY, -INFINITY, -INFINITY},
        point_ + optor::Vector3d{ INFINITY, -INFINITY, -INFINITY},
        point_ + optor::Vector3d{-INFINITY,  INFINITY, -INFINITY},
        point_ + optor::Vector3d{ INFINITY,  INFINITY, -INFINITY},
        point_ + optor::Vector3d{-INFINITY, -INFINITY,  INFINITY},
        point_ + optor::Vector3d{ INFINITY, -INFINITY,  INFINITY},
        point_ + optor::Vector3d{-INFINITY,  INFINITY,  INFINITY},
        point_ + optor::Vector3d{ INFINITY,  INFINITY,  INFINITY}
    };
optor::Vector3d optor::Plane::GetCoord() const {
    return point_;
}