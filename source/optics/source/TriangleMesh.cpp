#include "optics/TriangleMesh.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Triangle.hpp"


optor::TriangleMesh::TriangleMesh(const Material& material)
    : optor::OpticObj(material)
{}

void optor::TriangleMesh::AddTriangle(const Triangle& triangle) {
    ERROR_HANDLE([this, &triangle](){
        triangles_.push_back(triangle);
    });
    ERROR_HANDLE([this](){
        triangles_.back().SetMaterial(material_);
    });
}

void optor::TriangleMesh::Clear() noexcept {
    triangles_.clear();
}

std::optional<optor::OpticObj::Intersection> 
optor::TriangleMesh::IntersectRay(const optor::Vector3d& rayOrigin, const optor::Vector3d& rayDir)
{
    std::optional<Intersection> closestHit;
    double minDist = std::numeric_limits<double>::max();

    for (auto& triangle : triangles_) 
    {
        auto hit = triangle.IntersectRay(rayOrigin, rayDir);
        if (hit && hit->distance < minDist) 
        {
            minDist = hit->distance;
            closestHit = hit;
            closestHit->object = this;
        }
    }

    return closestHit;
}

void optor::TriangleMesh::SetMaterial(const Material& material) {
    for (auto& triangle : triangles_) {
        ERROR_HANDLE(&optor::Triangle::SetMaterial, triangle, material);
    }

    ERROR_HANDLE([this, &material](){
        optor::OpticObj::SetMaterial(material);
    });
}

void optor::TriangleMesh::Move(const optor::Vector3d& offset) {
    for (auto& triangle : triangles_) {
        ERROR_HANDLE(&optor::Triangle::Move, triangle, offset);
    }
}