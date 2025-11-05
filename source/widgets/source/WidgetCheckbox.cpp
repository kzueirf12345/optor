#include "dr4/texture.hpp"

#include "global/Global.hpp"
#include "widgets/Widget.hpp"
#include "widgets/WidgetButton.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetCheckbox.hpp"

optor::WidgetCheckbox::WidgetCheckbox(dr4::Window* window, const ::dr4::Vec2f& size, 
                                      optor::WidgetsState* state, ActionT action, bool isPressed)
    :   optor::WidgetButton(size, state),\
        texture_{window->CreateTexture()},
        action_(action),
        pressedText_{.text = "V", .color = optor::color::TextPrimary, .font = optor::FONT }
{
    isPressed_ = isPressed;
    
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_.rect.size);
    });

    ERROR_HANDLE([this, &size](){
        const ::dr4::Vec2f localBounds = pressedText_.GetBounds().size;
        pressedText_.pos.x = (size.x - localBounds.x) / 2;
        pressedText_.pos.y = (size.y - localBounds.y) / 2;
    });
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

    const ::dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    if (isPressed_) {
        ERROR_HANDLE([this](){
            texture_->Draw(pressedText_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
    });
}