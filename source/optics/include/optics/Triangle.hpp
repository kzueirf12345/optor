#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLE_HPP

#include <optional>
#include "optics/Vector.hpp"
#include "optics/Material.hpp"
#include "optics/OpticObj.hpp"

namespace optor {

class TriangleMesh;

class Triangle : public OpticObj {
public:
    friend TriangleMesh;

public:
    Triangle(const optor::Vector3d& v0, const optor::Vector3d& v1, const optor::Vector3d& v2);
    Triangle(const optor::Vector3d& v0, const optor::Vector3d& v1, const optor::Vector3d& v2, const Material& material);

    [[nodiscard]] std::optional<Intersection> 
    IntersectRay(const optor::Vector3d& rayOrigin, const optor::Vector3d& rayDir) override;

    [[nodiscard]] const optor::Vector3d& GetNormal() const noexcept;

    virtual void Move(const optor::Vector3d& offset) override final;

    std::array<optor::Vector3d, 8> GetAABB() const override;
    virtual optor::Vector3d GetCoord() const override;

    virtual void WriteSerialize(FILE* file, size_t baseTabCnt) const override;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "Triangle"; };

private:
    optor::Vector3d v0_, v1_, v2_;
    optor::Vector3d normal_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_TRIANGLE_HPP*/
