#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP

#include <memory>

#include "hui/TexturedShape.hpp"
#include "optics/Camera.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Scene: public hui::TexturedShape {
    public:
        explicit Scene(const hui::Vector2d& boxSize);
        Scene(const hui::Vector2d& boxSize, const hui::Vector2d& position);

        virtual void Update();

        optor::OpticObj* AddObj(std::unique_ptr<optor::OpticObj> obj);

        [[nodiscard]] const optor::Camera& GetCamera() const noexcept;
        [[nodiscard]]       optor::Camera& GetCamera()       noexcept;

    private:
        std::vector<std::unique_ptr<optor::OpticObj>> objs_;

        optor::Camera camera_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP*/