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
            OpticObj* object;
        };

        OpticObj() = default;
        explicit OpticObj(const Material& material);
        virtual ~OpticObj() = default;
        
        [[nodiscard]] virtual std::optional<Intersection> 
            IntersectRay(const hui::Vector3d& rayBegin,const hui::Vector3d& rayDirection) = 0;

        [[nodiscard]] virtual const Material& GetMaterial() const noexcept { return material_; }
        virtual void SetMaterial(const Material& material) { material_ = material; }

        virtual void Move(const hui::Vector3d& offset) = 0;

    protected:
        optor::Material material_;

    private:
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP*/