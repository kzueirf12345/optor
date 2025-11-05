#include <cmath>

#include "global/Global.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Triangle.hpp"

optor::Triangle::Triangle(const optor::Vector3d& v0, const optor::Vector3d& v1, const optor::Vector3d& v2)
    : v0_(v0), v1_(v1), v2_(v2)
{
    normal_ = !((v1_ - v0_) * (v2_ - v0_));
}

optor::Triangle::Triangle(const optor::Vector3d& v0, const optor::Vector3d& v1, const optor::Vector3d& v2, const Material& material)
    : optor::OpticObj(material), v0_(v0), v1_(v1), v2_(v2)
{
    normal_ = !((v1_ - v0_) * (v2_ - v0_));
}

std::optional<optor::OpticObj::Intersection> 
optor::Triangle::IntersectRay(const optor::Vector3d& rayOrigin, const optor::Vector3d& rayDirection) 
{
    optor::Vector3d edgeA = v1_ - v0_;
    optor::Vector3d edgeB = v2_ - v0_;

    optor::Vector3d directionCrossEdgeB = rayDirection * edgeB;
    double determinant = edgeA ^ directionCrossEdgeB;

    if (std::abs(determinant) < EPSILON)
        return std::nullopt;

    double invDeterminant = 1 / determinant;

    optor::Vector3d originToVertex0 = rayOrigin - v0_;
    double u = (originToVertex0 ^ directionCrossEdgeB) * invDeterminant;
    if (u < 0 || u > 1)
        return std::nullopt;

    optor::Vector3d originCrossEdgeA = originToVertex0 * edgeA;
    double v = (rayDirection ^ originCrossEdgeA) * invDeterminant;
    if (v < 0 || u + v > 1)
        return std::nullopt;

    double t = (edgeB ^ originCrossEdgeA) * invDeterminant;
    if (t < 0)
        return std::nullopt;

    optor::Vector3d intersectionPoint = rayOrigin + rayDirection * t;

    return Intersection{t, intersectionPoint, normal_, this};
}


const optor::Vector3d& optor::Triangle::GetNormal() const noexcept {
    return normal_;
}

void optor::Triangle::Move(const optor::Vector3d& offset) {
    v0_ += offset;
    v1_ += offset;
    v2_ += offset;
}

std::array<optor::Vector3d, 8> optor::Triangle::GetAABB() const
{
    const double minX = std::min({v0_.x, v1_.x, v2_.x});
    const double minY = std::min({v0_.y, v1_.y, v2_.y});
    const double minZ = std::min({v0_.z, v1_.z, v2_.z});

    const double maxX = std::max({v0_.x, v1_.x, v2_.x});
    const double maxY = std::max({v0_.y, v1_.y, v2_.y});
    const double maxZ = std::max({v0_.z, v1_.z, v2_.z});

    const optor::Vector3d minPoint{minX, minY, minZ};
    const optor::Vector3d maxPoint{maxX, maxY, maxZ};

    return {
        optor::Vector3d{minPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, maxPoint.z}
    };
optor::Vector3d optor::Triangle::GetCoord() const {
    return (v0_ + v1_ + v2_) / 3.0;
}
std::array<optor::Vector3d, 8> optor::Triangle::GetAABB() const
{
    const double minX = std::min({v0_.x, v1_.x, v2_.x});
    const double minY = std::min({v0_.y, v1_.y, v2_.y});
    const double minZ = std::min({v0_.z, v1_.z, v2_.z});

    const double maxX = std::max({v0_.x, v1_.x, v2_.x});
    const double maxY = std::max({v0_.y, v1_.y, v2_.y});
    const double maxZ = std::max({v0_.z, v1_.z, v2_.z});

    const optor::Vector3d minPoint{minX, minY, minZ};
    const optor::Vector3d maxPoint{maxX, maxY, maxZ};

    return {
        optor::Vector3d{minPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, maxPoint.z}
    };
}
