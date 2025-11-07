#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_FINITPLANE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_FINITPLANE_HPP

#include "OpticObj.hpp"
#include "TriangleMesh.hpp"
#include "Material.hpp"
#include "optics/Vector.hpp"

namespace optor
{

class FinitPlane : public OpticObj {
    public:
        FinitPlane(const optor::Vector3d& center, const optor::Vector3d& normal, const optor::Vector2d& size);
        FinitPlane(const optor::Vector3d& center, const optor::Vector3d& normal, const optor::Vector2d& size,
                   const Material& material);

        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const optor::Vector3d& rayOrigin,const optor::Vector3d& rayDir) override;

        [[nodiscard]] optor::Vector3d GetCenter() const noexcept;
        [[nodiscard]] optor::Vector3d GetNormal() const noexcept;
        [[nodiscard]] optor::Vector2d GetSize()   const noexcept;
        [[nodiscard]] double        GetWidth()  const noexcept;
        [[nodiscard]] double        GetHeight() const noexcept;

        void SetCenter  (const optor::Vector3d& center);
        void SetNormal  (const optor::Vector3d& normal);
        void SetSize    (const optor::Vector2d& size_);
        virtual void SetMaterial(const Material& material) override;

        virtual void Move(const optor::Vector3d& offset) override final;

        std::array<optor::Vector3d, 8> GetAABB() const override;
        virtual optor::Vector3d GetCoord() const override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "FinitPlane"; };

    private:
        optor::Vector3d center_;
        optor::Vector3d normal_;
        optor::Vector2d size_;
        TriangleMesh mesh_;

        void BuildMesh();
};

}

#endif /* OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_FINITPLANE_HPP */
