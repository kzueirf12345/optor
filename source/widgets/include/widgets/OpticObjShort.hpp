#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP
#include "dr4/texture.hpp"

#include "dr4/window.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/WidgetText.hpp"

namespace optor 
{

class OpticObjShort : public WidgetText {
    public:
        OpticObjShort(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, optor::OpticObj* obj);

        virtual void OnIdle() override;

        const optor::OpticObj* GetObj() const noexcept;

    private:
        optor::OpticObj* obj_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP*/