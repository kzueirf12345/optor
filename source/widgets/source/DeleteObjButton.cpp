#include "widgets/DeleteObjButton.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/mouse_buttons.hpp"
#include "widgets/Widget.hpp"

        
optor::DeleteObjButton::DeleteObjButton(const dr4::Vec2f& size, optor::WidgetsState* state, 
                const std::string& text, optor::OpticObjShort* desc) 
    :   optor::WidgetButton(size, state),
        optor::Textable(text, state->window),
        texture_{state->window->CreateTexture()},
        desc_{desc}
{
    ERROR_HANDLE([this, &size](){
        texture_->SetSize(size);
    });

    
    ERROR_HANDLE([this, &size](){
        const dr4::Vec2f localBounds = text_->GetBounds();
        text_->SetPos((size.x - localBounds.x) / 2,
                      (size.y - localBounds.y) / 2);
    });
}

void optor::DeleteObjButton::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

bool optor::DeleteObjButton::OnMousePress(const ::dr4::Event &event) {
    if (isHide_) return false;

    if (state_->hoveredWidget == this && event.mouseButton.button == dr4::MouseButtonType::LEFT) {
        isPressed_ = true;
        if (isSelectable_) { 
            state_->selectedWidget = this; 
        }
        rect_->SetFillColor(pressedColor_);

        desc_->SetMustRemoved(true);
        desc_->GetObj()->SetMustRemoved(true);
        this->SetMustRemoved(true);
        state_->needUpdateScene = true;

        if (desc_ == state_->selectedWidget) {
            state_->selectedWidget = nullptr;
        }

        if (desc_->GetObj() == state_->selectedObj) {
            state_->selectedObj = nullptr;
        }
        return true;
    }

    return false;
}
void optor::DeleteObjButton::OnIdle() {
    if (isHide_) return;
}

void optor::DeleteObjButton::Draw(dr4::Texture &srcTexture) {
    if (isHide_) return;

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}