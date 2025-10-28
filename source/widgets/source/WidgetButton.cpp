#include "widgets/WidgetButton.hpp"
#include "hui/RectangleShape.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetButton::WidgetButton(hui::RectangleShape rect, optor::WidgetsState* state)
    :   optor::Widget{std::move(rect), state},
        isPressed_{false},
        pressButton_{optor::INIT_PRESS_BUTTON_BUTTON_},
        pressedColor_(optor::color::Cyan),
        releasedColor_(rect_.GetFillColor())
{
    ERROR_HANDLE([this](){SetIsDraggable(false);});
}

bool optor::WidgetButton::OnMousePress  (const hui::Event& event) {
    if (state_->hoveredWidget == this && event.GetMouseButton() == pressButton_) {
        isPressed_ = true;
        state_->selectedWidget = this;
        ERROR_HANDLE(&hui::RectangleShape::SetFillColor, rect_, pressedColor_);
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
        ERROR_HANDLE(&hui::RectangleShape::SetFillColor, rect_, releasedColor_);
        return true;
    }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMouseRelease(event);})) {
        return true;
    }

    return false;
}