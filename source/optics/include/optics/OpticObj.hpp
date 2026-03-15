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

        OpticObj();
        explicit OpticObj(const Material& material);
        virtual ~OpticObj() = default;
        
        [[nodiscard]] virtual std::optional<Intersection> 
            IntersectRay(const optor::Vector3d& rayBegin,const optor::Vector3d& rayDirection) = 0;

        [[nodiscard]] virtual const Material& GetMaterial() const noexcept { return material_; }
        [[nodiscard]] virtual optor::Vector3d GetAmbientColor() const noexcept { return material_.GetAmbientColor(); }
        [[nodiscard]] virtual optor::Vector3d GetDiffuseColor() const noexcept { return material_.GetDiffuseColor(); }
        [[nodiscard]] virtual optor::Vector3d GetSpecularColor() const noexcept { return material_.GetSpecularColor(); }

        [[nodiscard]] double GetShininess() { return material_.GetShininess(); }
        [[nodiscard]] double GetReflectivity() { return material_.GetReflectivity(); }
        [[nodiscard]] double GetTransparency() { return material_.GetTransparency(); }
        [[nodiscard]] double GetRefractivity() { return material_.GetRefractivity(); }

        virtual void SetMaterial(const Material& material) { material_ = material; }

        void SetAmbientColor(const optor::Vector3d& color) { material_.SetAmbientColor(color); }
        void SetAmbientColorX(double colorX) { material_.SetAmbientColorX(colorX); }
        void SetAmbientColorY(double colorY) { material_.SetAmbientColorY(colorY); }
        void SetAmbientColorZ(double colorZ) { material_.SetAmbientColorZ(colorZ); }

        void SetDiffuseColor(const optor::Vector3d& color) { material_.SetDiffuseColor(color); }
        void SetDiffuseColorX(double colorX) { material_.SetDiffuseColorX(colorX); }
        void SetDiffuseColorY(double colorY) { material_.SetDiffuseColorY(colorY); }
        void SetDiffuseColorZ(double colorZ) { material_.SetDiffuseColorX(colorZ); }

        void SetSpecularColor(const optor::Vector3d& color) { material_.SetSpecularColor(color); }
        void SetSpecularColorX(double colorX) { material_.SetSpecularColorX(colorX); }
        void SetSpecularColorY(double colorY) { material_.SetSpecularColorY(colorY); }
        void SetSpecularColorZ(double colorZ) { material_.SetSpecularColorZ(colorZ); }

        void SetShininess(double shininess) { material_.SetShininess(shininess); }
        void SetReflectivity(double reflectivity) { material_.SetReflectivity(reflectivity); }
        void SetTransparency(double transparency) { material_.SetTransparency(transparency); }
        void SetRefractivity(double refractivity) { material_.SetRefractivity(refractivity); }

        virtual void WriteSerialize(FILE* file, size_t baseTabCnt) const ;

        virtual void SetCoord(const optor::Vector3d& pos) { Move(pos - GetCoord()); };
        virtual void Move(const optor::Vector3d& offset) = 0;

        virtual std::array<optor::Vector3d, 8> GetAABB() const = 0; 
        virtual optor::Vector3d GetCoord() const = 0;

        bool GetMustRemoved() const;
        void SetMustRemoved(bool mustRemoved);

        [[nodiscard]] virtual std::string GetTypeName() const {return "OpticObject"; };

    protected:
        optor::Material material_;

        bool mustRemoved_;

    private:
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_OPTICS_OBJ_HPP*/