#include "widgets/PiskaToolButton.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/window.hpp"

#include "pp/tool.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetButton.hpp"

optor::PiskaToolButton::PiskaToolButton(const dr4::Vec2f& size, 
                                              optor::WidgetsState* state,
                                              pp::Tool* tool, pp::Tool** selectedTool)
    :   optor::WidgetButton(size, state),
        optor::Textable(std::string(tool->Icon()), state->window),
        texture_{state->window->CreateTexture()},
        tool_{tool},
        selectedTool_(selectedTool)
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

void optor::PiskaToolButton::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

bool optor::PiskaToolButton::OnMousePress  (const ::dr4::Event& event) {
    if (isHide_) { return false; }

    if (state_->hoveredWidget == this && event.mouseButton.button == pressButton_) {
        if (!isPressed_) {
            if (*selectedTool_) {
                (*selectedTool_)->OnEnd();
            }
            *selectedTool_ = tool_;
        } else {
            if (*selectedTool_) {
                (*selectedTool_)->OnEnd();
            }
            *selectedTool_ = nullptr;
        }
        return true;
    }

    return optor::Widget::OnMousePress(event);
}

bool optor::PiskaToolButton::OnMouseRelease(const ::dr4::Event& event) {
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){return optor::Widget::OnMouseRelease(event);})) {
        return true;
    }

    return false;
}

bool optor::PiskaToolButton::OnKeyboardPress(const dr4::Event& event) {
    if (isHide_) { return false; }

    if (event.key.sym == dr4::KeyCode::KEYCODE_ESCAPE && *selectedTool_ == tool_ && tool_->IsCurrentlyDrawing()) {
        (*selectedTool_)->OnBreak();
        return true;
    }

    return optor::WidgetButton::OnKeyboardPress(event);
}

void optor::PiskaToolButton::OnIdle() {
    if (*selectedTool_ == tool_) {
        isPressed_ = true;
        rect_->SetFillColor(pressedColor_);
    } else {
        isPressed_ = false;
        rect_->SetFillColor(releasedColor_);
    }

    optor::WidgetButton::OnIdle();
}

void optor::PiskaToolButton::Draw(dr4::Texture &srcTexture) {
    if (isHide_) { return; }

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