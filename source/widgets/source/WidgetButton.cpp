#include "widgets/WidgetButton.hpp"
#include "hui/Texture.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetButton::WidgetButton(const hui::Vector2d& size, optor::WidgetsState* state)
    :   optor::Widget{size, state},
        isPressed_{false},
        pressButton_{optor::INIT_PRESS_BUTTON_BUTTON_},
        pressedColor_(optor::color::ButtonPressed),
        releasedColor_(optor::color::ButtonReleased)
{
    ERROR_HANDLE([this](){texture_.Fill(releasedColor_);});
    ERROR_HANDLE([this](){SetIsDraggable(false);});
}

bool optor::WidgetButton::OnMousePress  (const hui::Event& event) {
    if (state_->hoveredWidget == this && event.GetMouseButton() == pressButton_) {
        isPressed_ = true;
        if (isSelectable_) { state_->selectedWidget = this; }
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

void optor::WidgetButton::SetReleasedColor(const hui::Color& color) {
    releasedColor_ = color;
    if (!isPressed_) {
        ERROR_HANDLE(&hui::Texture::Fill, texture_, releasedColor_);
    }
}
void optor::WidgetButton::SetPressedColor (const hui::Color& color) {
    pressedColor_ = color;
    if (isPressed_) {
        ERROR_HANDLE(&hui::Texture::Fill, texture_, pressedColor_);
    }
}

bool optor::WidgetButton::IsPressed() const noexcept { return isPressed_; }