#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_FINITPLANE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_FINITPLANE_HPP

#include "OpticObj.hpp"
#include "TriangleMesh.hpp"
#include "Material.hpp"
#include "hui/Vector.hpp"

namespace optor
{

class FinitPlane final : public OpticObj {
    public:
        FinitPlane(const hui::Vector3d& center, const hui::Vector3d& normal, const hui::Vector2d& size);
        FinitPlane(const hui::Vector3d& center, const hui::Vector3d& normal, const hui::Vector2d& size,
                   const Material& material);

        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const hui::Vector3d& rayOrigin,const hui::Vector3d& rayDir) const override;

        [[nodiscard]] hui::Vector3d GetCenter() const noexcept;
        [[nodiscard]] hui::Vector3d GetNormal() const noexcept;
        [[nodiscard]] hui::Vector2d GetSize()   const noexcept;
        [[nodiscard]] double        GetWidth()  const noexcept;
        [[nodiscard]] double        GetHeight() const noexcept;

        void SetCenter  (const hui::Vector3d& center);
        void SetNormal  (const hui::Vector3d& normal);
        void SetSize    (const hui::Vector2d& size_);
        virtual void SetMaterial(const Material& material) override;

    private:
        hui::Vector3d center_;
        hui::Vector3d normal_;
        hui::Vector2d size_;
        TriangleMesh mesh_;

        void BuildMesh();
};

}

#endif /* OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_FINITPLANE_HPP */
