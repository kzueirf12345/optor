#include "widgets/WidgetButton.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetButton::WidgetButton(const ::dr4::Vec2f& size, optor::WidgetsState* state)
    :   optor::Widget{size, state},
        isPressed_{false},
        pressButton_{optor::INIT_PRESS_BUTTON_BUTTON_},
        pressedColor_(optor::color::ButtonPressed),
        releasedColor_(optor::color::ButtonReleased)
{
    rect_.fill = releasedColor_;
    ERROR_HANDLE([this](){SetIsDraggable(false);});
}

bool optor::WidgetButton::OnMousePress  (const ::dr4::Event& event) {
    if (isHide_) { return false; }

    if (state_->hoveredWidget == this && event.mouseButton.button == pressButton_) {
        isPressed_ = true;
        if (isSelectable_) { 
            state_->selectedWidget = this; 
        }
        rect_.fill = pressedColor_;
        return true;
    }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMousePress(event);})) {
        return true;
    }

    return false;
}

bool optor::WidgetButton::OnMouseRelease(const ::dr4::Event& event) {
    if (isHide_) { return false; }
    
    if (isPressed_ && event.mouseButton.button == pressButton_) {
        isPressed_ = false;
        rect_.fill = releasedColor_;
        return true;
    }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMouseRelease(event);})) {
        return true;
    }

    return false;
}

void optor::WidgetButton::SetReleasedColor(const ::dr4::Color& color) {
    releasedColor_ = color;
    if (!isPressed_) {
        rect_.fill = releasedColor_;
    }
}
void optor::WidgetButton::SetPressedColor (const ::dr4::Color& color) {
    pressedColor_ = color;
    if (isPressed_) {
        rect_.fill = pressedColor_;
    }
}

bool optor::WidgetButton::IsPressed() const noexcept { 
    return isPressed_; 
}