#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP

#include <optional>

#include "hui/Vector.hpp"
#include "optics/Material.hpp"

namespace optor 
{


class OpticObj {
    public:
        struct Intersection {
            double distance;
            hui::Vector3d point;
            hui::Vector3d normal;
            const OpticObj* object;
        };

        OpticObj() = default;
        virtual ~OpticObj() = default;
        
        [[nodiscard]] virtual bool IsContainsDot(const hui::Vector3d& dot) const noexcept = 0;
        
        [[nodiscard]] virtual std::optional<Intersection> 
            IntersectRay(const hui::Vector3d& rayBegin,const hui::Vector3d& rayDirection) const = 0;

        [[nodiscard]] virtual hui::Vector3d GetNormal(const hui::Vector3d& dot) const = 0;

        [[nodiscard]] const Material& GetMaterial() const noexcept { return material_; }
        void SetMaterial(const Material& material) { material_ = material; }

    protected:
        optor::Material material_;

    private:
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP*/