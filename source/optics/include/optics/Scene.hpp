#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP

#include <memory>
#include <vector>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "misc/dr4_ifc.hpp"

#include "optics/Vector.hpp"
#include "optics/Camera.hpp"
#include "optics/Light.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Scene {
    public:
        Scene(dr4::DR4Backend* backend, const dr4::Vec2f& size);

        virtual void Update();

        optor::OpticObj* AddObj(std::unique_ptr<optor::OpticObj> obj);

        [[nodiscard]] const optor::Camera& GetCamera() const ;
        [[nodiscard]]       optor::Camera& GetCamera();
        [[nodiscard]] optor::MoveDirection GetMoveDir() const ;

        [[nodiscard]] const std::vector<std::unique_ptr<optor::OpticObj>>& GetObjs() const ;
        [[nodiscard]] dr4::Image* GetImage() const;

        void SetMoveDir(optor::MoveDirection moveDir);

        OpticObj* GetObjAtPixel(const optor::Vector2d& pixel);

    private:
        std::unique_ptr<dr4::Image> image_;
        dr4::Vec2f size_;

        std::vector<std::unique_ptr<optor::OpticObj>> objs_;
        std::vector<optor::Light*> lights_;

        optor::Camera camera_;

        optor::MoveDirection moveDir_;

        int maxRecursionDepth_; 
        optor::Vector3d bgColor_;
        
        optor::Vector3d TraceRay(const optor::Vector3d& origin, const optor::Vector3d& direction, int depth = 0) const;

        std::optional<optor::OpticObj::Intersection> 
        FindClosestIntersection(const optor::Vector3d& origin, const optor::Vector3d& direction) const;

        optor::Vector3d CalculateLighting(const optor::OpticObj::Intersection& intersection, 
                                          const optor::Vector3d& rayOrigin, int depth = 0) const;

        bool IsInShadow(const optor::Vector3d& point, const optor::Vector3d& lightDir, double lightDistance, const optor::OpticObj* obj) const;

        optor::Vector3d Reflect(const optor::Vector3d& incident, const optor::Vector3d& normal) const;
        std::optional<optor::Vector3d> Refract(const optor::Vector3d& incident, 
                                               const optor::Vector3d& normal, 
                                               double eta) const;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP*/