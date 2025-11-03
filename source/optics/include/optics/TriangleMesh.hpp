#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLEMESH_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLEMESH_HPP

#include "OpticObj.hpp"
#include "Triangle.hpp"
#include "Material.hpp"
#include <vector>
#include <optional>

namespace optor
{

class TriangleMesh final : public OpticObj {
    public:
        TriangleMesh() = default;
        explicit TriangleMesh(const Material& material);

        void AddTriangle(const Triangle& triangle);
        void Clear() noexcept;

        [[nodiscard]] std::optional<Intersection> IntersectRay(const optor::Vector3d& rayOrigin, 
                                                            const optor::Vector3d& rayDir) override;
        
        virtual void SetMaterial(const Material& material) override;

        virtual void Move(const optor::Vector3d& offset) override final;

    private:
        std::vector<Triangle> triangles_;
};

}

#endif /* OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLEMESH_HPP */
