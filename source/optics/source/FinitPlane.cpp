#include <cmath>

#include "optics/FinitPlane.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Triangle.hpp"
#include "optics/TriangleMesh.hpp"


optor::FinitPlane::FinitPlane(const hui::Vector3d& center, const hui::Vector3d& normal, 
                              const hui::Vector2d& size)
    :   center_(center),
        normal_(!normal),
        size_(size),
        mesh_()
{
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

optor::FinitPlane::FinitPlane(const hui::Vector3d& center,const hui::Vector3d& normal, 
                              const hui::Vector2d& size, const Material& material)
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

    hui::Vector3d arbitraryUp = std::fabs(normal_.y) < 0.99 ? hui::Vector3d(0, 1, 0) : hui::Vector3d(1, 0, 0);

    hui::Vector3d tangent   = !(arbitraryUp * normal_);
    hui::Vector3d bitangent = !(normal_ * tangent);

    hui::Vector3d halfTangent   = tangent   * (size_.x / 2.0);
    hui::Vector3d halfBitangent = bitangent * (size_.y / 2.0);

    hui::Vector3d v0 = center_ - halfTangent - halfBitangent;
    hui::Vector3d v1 = center_ + halfTangent - halfBitangent;
    hui::Vector3d v2 = center_ + halfTangent + halfBitangent;
    hui::Vector3d v3 = center_ - halfTangent + halfBitangent;

    ERROR_HANDLE(&optor::TriangleMesh::AddTriangle, mesh_, optor::Triangle{v0, v1, v2});
    ERROR_HANDLE(&optor::TriangleMesh::AddTriangle, mesh_, optor::Triangle{v0, v2, v3});
}

std::optional<optor::OpticObj::Intersection> 
optor::FinitPlane::IntersectRay(const hui::Vector3d& rayOrigin, const hui::Vector3d& rayDir) {
    return ERROR_HANDLE(&optor::TriangleMesh::IntersectRay, mesh_, rayOrigin, rayDir);
}


hui::Vector3d optor::FinitPlane::GetCenter() const noexcept { return center_; }
hui::Vector3d optor::FinitPlane::GetNormal() const noexcept { return normal_; }
hui::Vector2d optor::FinitPlane::GetSize()   const noexcept { return size_; }
double        optor::FinitPlane::GetWidth()  const noexcept { return size_.x; }
double        optor::FinitPlane::GetHeight() const noexcept { return size_.y; }

void optor::FinitPlane::SetCenter(const hui::Vector3d& center) {
    center_ = center;
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::SetNormal(const hui::Vector3d& normal) {
    normal_ = !normal;
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::SetSize(const hui::Vector2d& size) {
    size_ = size;
    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}

void optor::FinitPlane::SetMaterial(const Material& material) {
    ERROR_HANDLE(&optor::TriangleMesh::SetMaterial, mesh_, material);

    ERROR_HANDLE([this, &material](){
        optor::OpticObj::SetMaterial(material);
    });
}

void optor::FinitPlane::Move(const hui::Vector3d& offset) {
    center_ += offset;

    ERROR_HANDLE(&optor::FinitPlane::BuildMesh, this);
}
