#include <cmath>

#include "optics/FinitPlane.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Triangle.hpp"
#include "optics/TriangleMesh.hpp"


optor::FinitPlane::FinitPlane(const optor::Vector3d& center, const optor::Vector3d& normal, 
                              const optor::Vector2d& size)
    :   center_(center),
        normal_(!normal),
        size_(size),
        mesh_()
{
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

optor::FinitPlane::FinitPlane(const optor::Vector3d& center,const optor::Vector3d& normal, 
                              const optor::Vector2d& size, const Material& material)
    :   optor::OpticObj(material),
        center_(center),
        normal_(!normal),
        size_(size),
        mesh_(material)
{
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::BuildMesh() {
    mesh_.Clear();

    optor::Vector3d arbitraryUp = std::fabs(normal_.y) < 0.99 ? optor::Vector3d(0, 1, 0) : optor::Vector3d(1, 0, 0);

    optor::Vector3d tangent   = !(arbitraryUp * normal_);
    optor::Vector3d bitangent = !(normal_ * tangent);

    optor::Vector3d halfTangent   = tangent   * (size_.x / 2.0);
    optor::Vector3d halfBitangent = bitangent * (size_.y / 2.0);

    optor::Vector3d v0 = center_ - halfTangent - halfBitangent;
    optor::Vector3d v1 = center_ + halfTangent - halfBitangent;
    optor::Vector3d v2 = center_ + halfTangent + halfBitangent;
    optor::Vector3d v3 = center_ - halfTangent + halfBitangent;

    ERROR_HANDLE(&optor::TriangleMesh::AddTriangle, mesh_, optor::Triangle{v0, v1, v2});
    ERROR_HANDLE(&optor::TriangleMesh::AddTriangle, mesh_, optor::Triangle{v0, v2, v3});
}

std::optional<optor::OpticObj::Intersection> 
optor::FinitPlane::IntersectRay(const optor::Vector3d& rayOrigin, const optor::Vector3d& rayDir) {
    return ERROR_HANDLE(&optor::TriangleMesh::IntersectRay, mesh_, rayOrigin, rayDir);
}


optor::Vector3d optor::FinitPlane::GetCenter() const noexcept { return center_; }
optor::Vector3d optor::FinitPlane::GetNormal() const noexcept { return normal_; }
optor::Vector2d optor::FinitPlane::GetSize()   const noexcept { return size_; }
double        optor::FinitPlane::GetWidth()  const noexcept { return size_.x; }
double        optor::FinitPlane::GetHeight() const noexcept { return size_.y; }

void optor::FinitPlane::SetCenter(const optor::Vector3d& center) {
    center_ = center;
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::SetNormal(const optor::Vector3d& normal) {
    normal_ = !normal;
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::SetSize(const optor::Vector2d& size) {
    size_ = size;
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::SetMaterial(const Material& material) {
    ERROR_HANDLE(&optor::TriangleMesh::SetMaterial, mesh_, material);

    ERROR_HANDLE([this, &material](){
        optor::OpticObj::SetMaterial(material);
    });
}

void optor::FinitPlane::Move(const optor::Vector3d& offset) {
    center_ += offset;

    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

optor::Vector3d optor::FinitPlane::GetCoord() const {
    return center_;
}
