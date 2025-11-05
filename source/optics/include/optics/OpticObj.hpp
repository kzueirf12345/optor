#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP

#include <optional>
#include <string>
#include <array>

#include "optics/Vector.hpp"
#include "optics/Material.hpp"

namespace optor 
{


class OpticObj {
    public:
        struct Intersection {
            double distance;
            optor::Vector3d point;
            optor::Vector3d normal;
            OpticObj* object;
        };

        OpticObj() = default;
        explicit OpticObj(const Material& material);
        virtual ~OpticObj() = default;
        
        [[nodiscard]] virtual std::optional<Intersection> 
            IntersectRay(const optor::Vector3d& rayBegin,const optor::Vector3d& rayDirection) = 0;

        [[nodiscard]] virtual const Material& GetMaterial() const noexcept { return material_; }
        virtual void SetMaterial(const Material& material) { material_ = material; }

        virtual void Move(const optor::Vector3d& offset) = 0;

        virtual std::array<optor::Vector3d, 8> GetAABB() const = 0; 
        virtual optor::Vector3d GetCoord() const = 0;
        virtual std::array<optor::Vector3d, 8> GetAABB() const = 0; 

        [[nodiscard]] virtual std::string GetTypeName() const {return "OpticObject"; };

    protected:
        optor::Material material_;

    private:
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP*/