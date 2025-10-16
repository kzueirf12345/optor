#include <optional>

#include "optics/Sphere.hpp"
#include "hui/Color.hpp"
#include "hui/Vector.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::Sphere::Sphere(double radius)
    :   optor::Sphere::Sphere(radius, {0, 0, 0})
{}

optor::Sphere::Sphere(double radius, const hui::Vector3d& center)
    :   radius_{radius},
        center_{center},
        radius2_{radius * radius},
        color_{optor::color::Transparent}
{}

bool optor::Sphere::IsContainsDot(const hui::Vector3d& dot) const noexcept {
    return dot.Len2() <= radius2_;
}

std::optional<double> optor::Sphere::IntersectRay(const hui::Vector3d& rayBegin, 
                                                  const hui::Vector3d& rayDirection) const {
    const hui::Vector3d oc = rayBegin - center_;
    
    const double a = rayDirection.Len2();
    const double b = 2.0 * (oc ^ rayDirection);
    const double c = oc.Len2() - radius2_;
    
    const double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return std::nullopt;
    }
    
    const double sqrtD = std::sqrt(discriminant);
    const double t1 = (-b - sqrtD) / (2 * a);
    const double t2 = (-b + sqrtD) / (2 * a);
    
    if (t1 > 0) return t1;
    if (t2 > 0) return t2;
    
    return std::nullopt;
}

std::optional<hui::Color> optor::Sphere::TraceRay(const hui::Vector3d& rayBegin, 
                                 const hui::Vector3d& rayDirection) const {
    if (ERROR_HANDLE(&optor::Sphere::IntersectRay, this, rayBegin, rayDirection)) {
        return color_;
    }
    return std::nullopt;
}

hui::Color optor::Sphere::GetColor() const noexcept {
    return color_;
}

void optor::Sphere::SetColor(const hui::Color& color) {
    color_ = color;
}