#include <cmath>
#include <optional>

#include "optics/Sphere.hpp"
#include "optics/OpticObj.hpp"

optor::Sphere::Sphere(double radius)
    :   optor::Sphere::Sphere(radius, {0, 0, 0})
{}

optor::Sphere::Sphere(double radius, const optor::Vector3d& center)
    :   radius_{radius},
        center_{center},
        radius2_{radius * radius}
{}

optor::Sphere::Sphere(double radius, const optor::Vector3d& center, const Material& material)
    :   optor::OpticObj(material),
        radius_{radius},
        center_{center},
        radius2_{radius * radius}
{}

std::optional<optor::OpticObj::Intersection> 
optor::Sphere::IntersectRay(const optor::Vector3d& rayBegin, const optor::Vector3d& rayDirection) 
{
    optor::Vector3d oc = rayBegin - center_;
    double a = rayDirection.Len2();
    double b = 2.0 * (oc ^ rayDirection);
    double c = oc.Len2() - radius2_;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return std::nullopt;
    }
    
    double sqrtd = std::sqrt(discriminant);
    double t1 = (-b - sqrtd) / (2.0 * a);
    double t2 = (-b + sqrtd) / (2.0 * a);
    
    double t = (t1 > 0 && t2 > 0) ? std::min(t1, t2) : 
               (t1 > 0)           ? t1 : 
               (t2 > 0)           ? t2 : std::numeric_limits<double>::infinity();

    if (t == std::numeric_limits<double>::infinity()) 
        return std::nullopt;
    
    optor::Vector3d point = rayBegin + rayDirection * t;
    optor::Vector3d normal = !(point - center_);
    
    return Intersection{t, point, normal, this};
}

const optor::Vector3d& optor::Sphere::GetCenter()  const noexcept {return center_;}
double               optor::Sphere::GetRadius()  const noexcept {return radius_;}
double               optor::Sphere::GetRadius2() const noexcept {return radius2_;}

void optor::Sphere::SetCenter(const optor::Vector3d& center) { center_ = center; }
void optor::Sphere::SetRadius(double radius) {
    radius_ = radius;
    radius2_ = radius * radius;
}

void optor::Sphere::Move(const optor::Vector3d& offset) {
    center_ += offset;
}