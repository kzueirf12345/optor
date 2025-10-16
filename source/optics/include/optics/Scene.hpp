#ifndef OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP
#define OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP

#include "hui/TexturedShape.hpp"
#include "optics/OpticObj.hpp"
#include <memory>

namespace optor 
{

class Scene: public hui::TexturedShape {
    public:
        explicit Scene(const hui::Vector2d& boxSize);
        Scene(const hui::Vector2d& boxSize, const hui::Vector2d& position);

        virtual void Update();

        optor::OpticObj* AddObj(std::unique_ptr<optor::OpticObj> obj);

    private:
        std::vector<std::unique_ptr<optor::OpticObj>> objs_;
};

}

#endif /*OPTOR_SOURCE_OPTICS_INCLUDE_OPTICS_SCENE_HPP*/