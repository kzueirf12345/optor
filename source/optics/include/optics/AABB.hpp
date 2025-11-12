#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_AABB_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_AABB_HPP

#include "OpticObj.hpp"
#include "TriangleMesh.hpp"
#include "Material.hpp"
#include "optics/Vector.hpp"
#include <array>
#include <optional>

namespace optor
{

class AABB : public OpticObj {
    public:
        AABB() = default;
        AABB(const std::array<optor::Vector3d, 8>& points);
        AABB(const std::array<optor::Vector3d, 8>& points, const Material& material);

        [[nodiscard]] std::optional<Intersection> 
            IntersectRay(const optor::Vector3d& rayOrigin, const optor::Vector3d& rayDir) override;

        [[nodiscard]] const std::array<optor::Vector3d, 8>& GetPoints() const noexcept;

        virtual void Move(const optor::Vector3d& offset) override final;
        virtual optor::Vector3d GetCoord() const override;
        virtual void SetMaterial(const Material& material) override;

        std::array<optor::Vector3d, 8> GetAABB() const override;

        [[nodiscard]] virtual std::string GetTypeName() const override { return "AABB"; };

        static inline constexpr double THICKNESS = 0.1;

    private:
        std::array<optor::Vector3d, 8> points_;
        TriangleMesh mesh_;

        void BuildMesh();
};

}

#endif /* OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_AABB_HPP */
