#include "widgets/OpticObjShort.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetText.hpp"

optor::OpticObjShort::OpticObjShort(optor::WidgetManager* manager, const dr4::Vec2f& size, optor::OpticObj* obj)
    :   optor::WidgetText(size, manager->GetState(), obj->GetTypeName()),
        obj_(obj),
        desktop_(manager->GetDesktop()),
        desc_{dr4::Vec2f(800, 600), manager->GetState(), obj},
        descButton_(dr4::KEYCODE_E)
{}

void optor::OpticObjShort::OnIdle() {
    if (isHide_) return;
    
    if (state_->selectedWidget == this) {
        state_->selectedObj = obj_;
    }

    if (state_->selectedObj == obj_) {
        text_->SetColor(optor::color::Green);
    } else {
        text_->SetColor(optor::color::TextPrimary);
    }

    optor::WidgetText::OnIdle();
}

const optor::OpticObj* optor::OpticObjShort::GetObj() const noexcept
{
    return obj_;
}

bool optor::OpticObjShort::OnKeyboardPress (const dr4::Event& event) {
    if (state_->selectedObj == obj_ && event.key.sym == descButton_) {
        auto* descWidget = ERROR_HANDLE(desc_, desktop_);
        descWidget->SetPosition(dr4::Vec2f(AbsCoord() + dr4::Vec2f{GetSize().x, 0}));
        return true;
    }

    return optor::WidgetText::OnKeyboardPress(event);
}