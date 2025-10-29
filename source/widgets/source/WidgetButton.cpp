#include "widgets/WidgetButton.hpp"
#include "hui/Texture.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetButton::WidgetButton(const hui::Vector2d& size, optor::WidgetsState* state)
    :   optor::Widget{size, state},
        isPressed_{false},
        pressButton_{optor::INIT_PRESS_BUTTON_BUTTON_},
        pressedColor_(optor::color::Cyan),
        releasedColor_(optor::color::WindowBackground)
{
    ERROR_HANDLE([this](){SetIsDraggable(false);});
}

bool optor::WidgetButton::OnMousePress  (const hui::Event& event) {
    if (state_->hoveredWidget == this && event.GetMouseButton() == pressButton_) {
        isPressed_ = true;
        state_->selectedWidget = this;
        ERROR_HANDLE(&hui::Texture::Fill, texture_, pressedColor_);
        spriteIsValid_ = false;
        return true;
    }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMousePress(event);})) {
        return true;
    }

    return false;
}

bool optor::WidgetButton::OnMouseRelease(const hui::Event& event) {
    if (isPressed_ && event.GetMouseButton() == pressButton_) {
        isPressed_ = false;
        ERROR_HANDLE(&hui::Texture::Fill, texture_, releasedColor_);
        spriteIsValid_ = false;
        return true;
    }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMouseRelease(event);})) {
        return true;
    }

    return false;
}