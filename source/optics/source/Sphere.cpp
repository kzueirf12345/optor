#include <optional>

#include "optics/Sphere.hpp"
#include "hui/Color.hpp"
#include "hui/Vector.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/Light.hpp"

optor::Sphere::Sphere(double radius)
    :   optor::Sphere::Sphere(radius, {0, 0, 0})
{}

optor::Sphere::Sphere(double radius, const hui::Vector3d& center)
    :   radius_{radius},
        center_{center},
        radius2_{radius * radius},
        ambientColor_{optor::color::Transparent.GetNormalized()},
        diffColor_{0.85, 0.1, 0.1},
        specColor_{1, 1, 1}
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

std::optional<hui::Color> optor::Sphere::TraceRay(const hui::Vector3d& rayDir,
                                                  const hui::Vector3d& cameraPos, 
                                                  const std::vector<optor::Light*>& lights) const {
    std::optional<double> distToIntersect = ERROR_HANDLE(
        &optor::Sphere::IntersectRay, 
        this, 
        cameraPos, 
        rayDir
    );
    
    if (!distToIntersect.has_value()) {
        return std::nullopt;
    }

    const hui::Vector3d intersectPoint = cameraPos + rayDir * distToIntersect.value();
    const hui::Vector3d normalVec = !(intersectPoint - center_);

    const hui::Vector3d ambientPart = ambientColor_ * GLOBAL_AMBIENT_COEF;

    hui::Vector3d diffPart(0, 0, 0);
    hui::Vector3d specPart(0, 0, 0);

    for (const auto& light : lights) {
        const hui::Vector3d lightDir = !(light->center_ - intersectPoint);
        const hui::Vector3d curEmmitColor = light->GetEmmitColor().GetNormalized();
        
        const double curDiffCoef = std::max(0., lightDir ^ normalVec); 

        
        const hui::Vector3d curDiffPart = hui::Product(diffColor_, curEmmitColor);
        
        diffPart += curDiffCoef * curDiffPart;
    }

    const hui::Vector3d resultColor(ambientPart + diffPart + specPart);

    return hui::Color(resultColor.Clump({0, 0, 0}, {1, 1, 1}));
}

hui::Color optor::Sphere::GetAmbientColor() const noexcept {
    return hui::Color(ambientColor_);
}

hui::Color optor::Sphere::GetDiffColor() const noexcept {
    return hui::Color(diffColor_);
}

hui::Color optor::Sphere::GetSpecColor() const noexcept {
    return hui::Color(specColor_);
}

void optor::Sphere::SetAmbientColor(const hui::Color& color) {
    ambientColor_ = color.GetNormalized();
}

void optor::Sphere::SetDiffColor(const hui::Color& color) {
    diffColor_ = color.GetNormalized();
}

void optor::Sphere::SetSpecColor(const hui::Color& color) {
    specColor_ = color.GetNormalized();
}