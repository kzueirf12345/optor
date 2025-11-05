#include "widgets/OpticObjShort.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetText.hpp"

optor::OpticObjShort::OpticObjShort(dr4::Window* window, const dr4::Vec2f& size, 
                                   optor::WidgetsState* state, optor::OpticObj* obj)
    :   optor::WidgetText(window, size, state, obj->GetTypeName()),
        obj_(obj)
{}

void optor::OpticObjShort::OnIdle() {
    if (isHide_) return;
    
    if (state_->selectedWidget == this) {
        state_->selectedObj = obj_;
    }

    if (state_->selectedObj == obj_) {
        text_.color = optor::color::Green;
    } else {
        text_.color = optor::color::TextPrimary;
    }

    optor::WidgetText::OnIdle();
}

const optor::OpticObj* optor::OpticObjShort::GetObj() const noexcept
{
    return obj_;
}