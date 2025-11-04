#include "widgets/HideButton.hpp"
#include "widgets/WidgetButton.hpp"
#include "common/ErrorHandler.hpp"

optor::HideButton::HideButton(const dr4::Vec2f& size, optor::WidgetsState* state, std::unique_ptr<optor::Widget> widget)
    :   optor::WidgetButton(size, state),
        widget_{nullptr}
{
    state_->modalWidgets.push_back(std::move(widget));
    widget_ = state_->modalWidgets.back().get();
}

bool optor::HideButton::OnMousePress  (const ::dr4::Event& event) {
    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMousePress(event);})) {
        return true;
    }

    return false;
}

bool optor::HideButton::OnMouseRelease(const ::dr4::Event& event) {
    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMouseRelease(event);})) {
        return true;
    }

    return false;
}

void optor::HideButton::OnIdle() {
    if (IsInderectedHovered() || widget_->IsInderectedHovered()) {
        isPressed_ = true;
        rect_.fill = pressedColor_;
        widget_->SetMustRemoved(false);
    } else {
        isPressed_ = false;
        rect_.fill = releasedColor_;
        widget_->SetMustRemoved(true);
    }

    return optor::WidgetButton::OnIdle();
}