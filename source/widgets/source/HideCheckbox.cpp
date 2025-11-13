#include "widgets/HideCheckbox.hpp"
#include "widgets/WidgetCheckbox.hpp"

optor::HideCheckbox::HideCheckbox(const ::dr4::Vec2f& size, optor::WidgetsState* state, 
                                  optor::Widget* widget)
    :   optor::WidgetCheckbox(
            size, 
            state, 
            [widget](bool isPressed){ widget->SetIsHide(!isPressed); }, 
            !widget->GetIsHide()
        ),
        widget_(widget)
{}

void optor::HideCheckbox::OnIdle() {
    if (isHide_) return;
    
    if (widget_->GetIsHide() == isPressed_) {
        isPressed_ = !isPressed_;
    }

    optor::WidgetCheckbox::OnIdle();
}