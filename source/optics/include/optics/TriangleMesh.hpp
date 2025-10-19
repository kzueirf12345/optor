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
        void AddTriangle(const hui::Vector3d& v0, const hui::Vector3d& v1, const hui::Vector3d& v2);

        [[nodiscard]] std::optional<Intersection> IntersectRay(const hui::Vector3d& rayOrigin, 
                                                            const hui::Vector3d& rayDir) const override;

    private:
        std::vector<Triangle> triangles_;
};

}

#endif /* OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLEMESH_HPP */
