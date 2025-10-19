#include "optics/TriangleMesh.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/OpticObj.hpp"


optor::TriangleMesh::TriangleMesh(const Material& material)
    : optor::OpticObj(material)
{}

void optor::TriangleMesh::AddTriangle(const Triangle& triangle)
{
    ERROR_HANDLE([this, &triangle](){
        triangles_.push_back(triangle);
    });
    ERROR_HANDLE([this](){
        triangles_.back().SetMaterial(material_);
    });
}

std::optional<optor::OpticObj::Intersection> 
optor::TriangleMesh::IntersectRay(const hui::Vector3d& rayOrigin, const hui::Vector3d& rayDir) const 
{
    std::optional<Intersection> closestHit;
    double minDist = std::numeric_limits<double>::max();

    for (const auto& triangle : triangles_) 
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
