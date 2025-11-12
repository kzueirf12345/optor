#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP

#include "dr4/keycodes.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/OpticObjDesc.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/WidgetText.hpp"

namespace optor 
{

class OpticObjShort : public WidgetText {
    public:
        OpticObjShort(optor::WidgetManager* manager, const dr4::Vec2f& size, optor::OpticObj* obj);

        virtual void OnIdle() override;
        virtual bool OnKeyboardPress(const dr4::Event& event) override;

        const optor::OpticObj* GetObj() const noexcept;

    private:
        optor::OpticObj* obj_;

        optor::WidgetChildable* desktop_;

        OpticObjDesc desc_;

        dr4::KeyCode descButton_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_SHORT_HPP*/