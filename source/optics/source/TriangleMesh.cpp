#include "optics/TriangleMesh.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Triangle.hpp"
#include "optics/Vector.hpp"


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

optor::Vector3d optor::TriangleMesh::GetCoord() const {
    optor::Vector3d center = {0, 0, 0};
    for (const auto& triangle : triangles_) {
        center += triangle.GetCoord();
    }
    return center / (double)triangles_.size();
}

std::array<optor::Vector3d, 8> optor::TriangleMesh::GetAABB() const 
{
    if (triangles_.empty()) {
        const optor::Vector3d zero{0.0, 0.0, 0.0};
        return {
            zero, zero, zero, zero,
            zero, zero, zero, zero
        };
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();

    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    double maxZ = std::numeric_limits<double>::lowest();

    for (const auto& tri : triangles_) 
    {
        const auto aabb = tri.GetAABB();

        for (const auto& vertex : aabb) {
            if (vertex.x < minX) minX = vertex.x;
            if (vertex.y < minY) minY = vertex.y;
            if (vertex.z < minZ) minZ = vertex.z;

            if (vertex.x > maxX) maxX = vertex.x;
            if (vertex.y > maxY) maxY = vertex.y;
            if (vertex.z > maxZ) maxZ = vertex.z;
        }
    }

    const optor::Vector3d minPoint{minX, minY, minZ};
    const optor::Vector3d maxPoint{maxX, maxY, maxZ};

    return {
        optor::Vector3d{minPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, maxPoint.z}
    };
}
<<<<<<< HEAD
=======
optor::Vector3d optor::TriangleMesh::GetCoord() const {
    optor::Vector3d center = {0, 0, 0};
    for (const auto& triangle : triangles_) {
        center += triangle.GetCoord();
    }
    return center / (double)triangles_.size();
}
std::array<optor::Vector3d, 8> optor::TriangleMesh::GetAABB() const 
{
    if (triangles_.empty()) {
        const optor::Vector3d zero{0.0, 0.0, 0.0};
        return {
            zero, zero, zero, zero,
            zero, zero, zero, zero
        };
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();

    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    double maxZ = std::numeric_limits<double>::lowest();

    for (const auto& tri : triangles_) 
    {
        const auto aabb = tri.GetAABB();

        for (const auto& vertex : aabb) {
            if (vertex.x < minX) minX = vertex.x;
            if (vertex.y < minY) minY = vertex.y;
            if (vertex.z < minZ) minZ = vertex.z;

            if (vertex.x > maxX) maxX = vertex.x;
            if (vertex.y > maxY) maxY = vertex.y;
            if (vertex.z > maxZ) maxZ = vertex.z;
        }
    }

    const optor::Vector3d minPoint{minX, minY, minZ};
    const optor::Vector3d maxPoint{maxX, maxY, maxZ};

    return {
        optor::Vector3d{minPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, minPoint.z},
        optor::Vector3d{minPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, minPoint.y, maxPoint.z},
        optor::Vector3d{minPoint.x, maxPoint.y, maxPoint.z},
        optor::Vector3d{maxPoint.x, maxPoint.y, maxPoint.z}
    };
}
>>>>>>> 1b4b6ae (start deepseek not uspeshno)
