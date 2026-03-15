#include "optics/AABB.hpp"
#include "common/ErrorHandler.hpp"
#include <array>

optor::AABB::AABB(const std::array<optor::Vector3d, 8>& points)
    : points_(points), mesh_()
{
    ERROR_HANDLE(&optor::AABB::BuildMesh, this);
}

optor::AABB::AABB(const std::array<optor::Vector3d, 8>& points, const Material& material)
    : optor::OpticObj(material), points_(points), mesh_(material)
{
    ERROR_HANDLE(&optor::AABB::BuildMesh, this);
}

void optor::AABB::BuildMesh()
{
    mesh_.Clear();

    const auto& p = points_;

    const std::array<std::pair<int,int>,12> edges = {{
        {0,1},{1,3},{3,2},{2,0},
        {4,5},{5,7},{7,6},{6,4},
        {0,4},{1,5},{2,6},{3,7} 
    }};

    for (const auto& e : edges) {
        const Vector3d start = p[e.first];
        const Vector3d end   = p[e.second];

        Vector3d dir = end - start;
        Vector3d center = (start + end) * 0.5;

        Vector3d up = std::fabs(dir.y) < 0.99 ? Vector3d(0,1,0) : Vector3d(1,0,0);

        Vector3d tangent   = !(dir);
        Vector3d bitangent = !(tangent * up);

        Vector3d halfTangent   = tangent * (dir.Len()/2.0);
        Vector3d halfBitangent = bitangent * (THICKNESS/2.0);

        Vector3d v0 = center - halfTangent - halfBitangent;
        Vector3d v1 = center + halfTangent - halfBitangent;
        Vector3d v2 = center + halfTangent + halfBitangent;
        Vector3d v3 = center - halfTangent + halfBitangent;

        Triangle t1(v0,v1,v2);
        Triangle t2(v0,v2,v3);
        ERROR_HANDLE(&TriangleMesh::AddTriangle, mesh_, t1);
        ERROR_HANDLE(&TriangleMesh::AddTriangle, mesh_, t2);
    }
}


std::optional<optor::OpticObj::Intersection> 
optor::AABB::IntersectRay(const optor::Vector3d& rayOrigin, const optor::Vector3d& rayDir)
{
    return ERROR_HANDLE(&optor::TriangleMesh::IntersectRay, mesh_, rayOrigin, rayDir);
}

const std::array<optor::Vector3d, 8>& optor::AABB::GetPoints() const noexcept
{
    return points_;
}

void optor::AABB::Move(const optor::Vector3d& offset)
{
    for (auto& p : points_) {
        p += offset;
    }

    ERROR_HANDLE(&optor::AABB::BuildMesh, this);
}

optor::Vector3d optor::AABB::GetCoord() const
{
    optor::Vector3d center(0.0, 0.0, 0.0);
    for (const auto& p : points_) {
        center += p;
    }
    center /= 8.0;
    return center;
}

void optor::AABB::SetMaterial(const Material& material)
{
    ERROR_HANDLE(&optor::TriangleMesh::SetMaterial, mesh_, material);

    ERROR_HANDLE([this, &material]() {
        optor::OpticObj::SetMaterial(material);
    });
}


std::array<optor::Vector3d, 8> optor::AABB::GetAABB() const {
    return points_;
}

void optor::AABB::WriteSerialize(FILE* file, size_t baseTabCnt) const  {
    std::string baseIndent(baseTabCnt, ' ');
    std::string innerIndent(baseTabCnt + 4, ' ');
    std::string pointsIndent(baseTabCnt + 8, ' ');
    
    fprintf(file, "%s{\n", baseIndent.c_str());
    
    fprintf(file, "%s\"type\": \"%s\",\n", innerIndent.c_str(), GetTypeName().c_str());
    
    OpticObj::WriteSerialize(file, baseTabCnt + 4);
    
    fprintf(file, "%s\"points\": [\n", innerIndent.c_str());
    
    for (size_t i = 0; i < points_.size(); ++i) {
        const auto& point = points_[i];
        fprintf(file, "%s[%g, %g, %g]", pointsIndent.c_str(), point.x, point.y, point.z);
        
        if (i < points_.size() - 1) {
            fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    fprintf(file, "%s]\n", innerIndent.c_str());
    
    fprintf(file, "%s}", baseIndent.c_str());
}