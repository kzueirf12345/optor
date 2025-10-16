#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP

#include <memory>

#include "hui/TexturedShape.hpp"
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

        optor::OpticObj* AddObj  (std::unique_ptr<optor::OpticObj> obj);

        [[nodiscard]] const optor::Camera& GetCamera() const noexcept;
        [[nodiscard]]       optor::Camera& GetCamera()       noexcept;

    private:
        std::vector<std::unique_ptr<optor::OpticObj>> objs_;
        std::vector<optor::Light*> lights_;

        optor::Camera camera_;

        std::optional<hui::Color> TraceRay(const hui::Vector3d rayDir, const optor::OpticObj* obj, 
                                           double* dist);
        bool IsEclipse(const optor::OpticObj* obj, const optor::Light* light,
                          const hui::Vector3d& intersectPoint);
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP*/