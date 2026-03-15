#include "dr4/texture.hpp"

#include "global/Global.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetButton.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetCheckbox.hpp"

optor::WidgetCheckbox::WidgetCheckbox(const ::dr4::Vec2f& size, 
                                      optor::WidgetsState* state, ActionT action, bool isPressed)
    :   optor::WidgetButton(size, state),\
        texture_{state->window->CreateTexture()},
        action_(action),
        pressedText_{state->window->CreateText()}
{
    pressedText_->SetText("\uf42e");
    pressedText_->SetColor(optor::color::TextPrimary);
    pressedText_->SetFont(optor::FONT);
    pressedText_->SetFontSize(30);

    isPressed_ = isPressed;
    
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_->GetSize());
    });

    ERROR_HANDLE([this, &size](){
        const ::dr4::Vec2f localBounds = pressedText_->GetBounds();
        pressedText_->SetPos((size.x - localBounds.x) / 2,
                             (size.y - localBounds.y) / 2);
    });
}

void optor::WidgetCheckbox::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

bool optor::WidgetCheckbox::OnMousePress  (const ::dr4::Event& event) {
    if (isHide_) { return false; }

    if (state_->hoveredWidget == this && event.mouseButton.button == pressButton_) {
        isPressed_ = !isPressed_;
        if (isSelectable_) { 
            state_->selectedWidget = this; 
        }
        ERROR_HANDLE([this](){ action_(isPressed_); });
        // rect_.fill = (isPressed_ ? pressedColor_ : releasedColor_);
        return true;
    }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMousePress(event);})) {
        return true;
    }

    return false;
}
bool optor::WidgetCheckbox::OnMouseRelease(const ::dr4::Event& event) {
    if (isHide_) { return false; }

    return optor::Widget::OnMouseRelease(event);
}

void optor::WidgetCheckbox::Draw(::dr4::Texture &srcTexture) {
    if (isHide_) { return; }

    const ::dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    if (isPressed_) {
        ERROR_HANDLE([this](){
            texture_->Draw(*pressedText_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}