#include <cmath>

#include "global/Global.hpp"
#include "optics/Triangle.hpp"

optor::Triangle::Triangle(const hui::Vector3d& v0, const hui::Vector3d& v1, const hui::Vector3d& v2)
    : v0_(v0), v1_(v1), v2_(v2)
{
    normal_ = !((v1_ - v0_) * (v2_ - v0_));
}

std::optional<optor::OpticObj::Intersection> 
optor::Triangle::IntersectRay(const hui::Vector3d& rayOrigin, const hui::Vector3d& rayDirection) const 
{
    hui::Vector3d edgeA = v1_ - v0_;
    hui::Vector3d edgeB = v2_ - v0_;

    hui::Vector3d directionCrossEdgeB = rayDirection * edgeB;
    double determinant = edgeA ^ directionCrossEdgeB;

    if (std::abs(determinant) < EPSILON)
        return std::nullopt;

    double invDeterminant = 1 / determinant;

    hui::Vector3d originToVertex0 = rayOrigin - v0_;
    double u = (originToVertex0 ^ directionCrossEdgeB) * invDeterminant;
    if (u < 0 || u > 1)
        return std::nullopt;

    hui::Vector3d originCrossEdgeA = originToVertex0 * edgeA;
    double v = (rayDirection ^ originCrossEdgeA) * invDeterminant;
    if (v < 0 || u + v > 1)
        return std::nullopt;

    double t = (edgeB ^ originCrossEdgeA) * invDeterminant;
    if (t < 0)
        return std::nullopt;

    hui::Vector3d intersectionPoint = rayOrigin + rayDirection * t;

    return Intersection{t, intersectionPoint, normal_, this};
}


const hui::Vector3d& optor::Triangle::GetNormal() const noexcept {
    return normal_;
}

