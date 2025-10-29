#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP

#include <memory>

#include "hui/Textured.hpp"
#include "hui/Vector.hpp"
#include "optics/Camera.hpp"
#include "optics/Light.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Scene: public hui::Textured {
    public:
        explicit Scene(const hui::Vector2d& boxSize);
        Scene(const hui::Vector2d& boxSize, const hui::Vector2d& position);

        virtual void Update();

        optor::OpticObj* AddObj(std::unique_ptr<optor::OpticObj> obj);

        [[nodiscard]] const optor::Camera& GetCamera() const noexcept;
        [[nodiscard]]       optor::Camera& GetCamera()       noexcept;
        [[nodiscard]] optor::MoveDirection GetMoveDir() const noexcept;

        [[nodiscard]] const std::vector<std::unique_ptr<optor::OpticObj>>& GetObjs() const noexcept;

        void SetMoveDir(optor::MoveDirection moveDir);

        OpticObj* GetObjAtPixel(const hui::Vector2d& pixel);

    private:
        std::vector<std::unique_ptr<optor::OpticObj>> objs_;
        std::vector<optor::Light*> lights_;

        optor::Camera camera_;

        optor::MoveDirection moveDir_;

        int maxRecursionDepth_; 
        hui::Vector3d bgColor_;
        
        hui::Vector3d TraceRay(const hui::Vector3d& origin, const hui::Vector3d& direction, int depth = 0) const;

        std::optional<optor::OpticObj::Intersection> 
        FindClosestIntersection(const hui::Vector3d& origin, const hui::Vector3d& direction) const;

        hui::Vector3d CalculateLighting(const optor::OpticObj::Intersection& intersection, 
                                        const hui::Vector3d& rayOrigin, int depth = 0) const;

        bool IsInShadow(const hui::Vector3d& point, const hui::Vector3d& lightDir, double lightDistance, const optor::OpticObj* obj) const;

        hui::Vector3d Reflect(const hui::Vector3d& incident, const hui::Vector3d& normal) const;
        std::optional<hui::Vector3d> Refract(const hui::Vector3d& incident, 
                                             const hui::Vector3d& normal, 
                                             double eta) const;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP*/