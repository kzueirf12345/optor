#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP

#include <optional>

#include "hui/Vector.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Sphere: public optor::OpticObj {
    public:
        Sphere(double radius);
        Sphere(double radius, const hui::Vector3d& center);

        [[nodiscard]] virtual bool                      IsContainsDot(
                                                            const hui::Vector3d& dot
                                                        ) const noexcept override final;
        [[nodiscard]] virtual std::optional<double>     IntersectRay(
                                                            const hui::Vector3d& rayBegin, 
                                                            const hui::Vector3d& rayDirection
                                                        ) const          override final;

        [[nodiscard]] virtual hui::Vector3d GetNormal(const hui::Vector3d& dot) const override final;

        [[nodiscard]] hui::Vector3d GetCenter() const noexcept;

    protected:
        hui::Vector3d center_;
        double radius_;
        double radius2_;

};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SPHERE_HPP*/