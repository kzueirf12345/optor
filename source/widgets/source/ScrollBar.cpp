#include <cassert>
#include <algorithm>

#include "widgets/ScrollBar.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "widgets/WidgetButton.hpp"

optor::ScrollBar::ScrollBar(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                            ActionT action, bool isHorizontal)
    : optor::Widget(size, state),
      action_{std::move(action)},
      texture_{window->CreateTexture()},
      isHorizontal_{isHorizontal},
      buttonSize_{        
        (isHorizontal_ ? BUTTON_SIZE_PERCENT_ : 1.f) * rect_.rect.size.x,
        (!isHorizontal_ ? BUTTON_SIZE_PERCENT_ : 1.f) * rect_.rect.size.y
      },
      percentage_{0.0},
      incButton_(
          buttonSize_,
          state
      ),
      decButton_(
          buttonSize_,
          state
      ),
      thumbButton_(
          buttonSize_,
          state
      ),
      isPressedInc_{false},
      isPressedDec_{false}
{
    SetIsDraggable(false);

    ERROR_HANDLE([this](){
        texture_->SetSize(rect_.rect.size);
    });

    const dr4::Vec2f fullSize = rect_.rect.size;

    if (isHorizontal_) {
        decButton_.SetPosition({0, 0});
        incButton_.SetPosition({fullSize.x - buttonSize_.x, 0});
        thumbButton_.SetPosition({buttonSize_.x, 0});
    } else {
        decButton_.SetPosition({0, fullSize.y - buttonSize_.y});
        incButton_.SetPosition({0, 0});
        thumbButton_.SetPosition({0, buttonSize_.y});
    }

    incButton_.SetParent(this);
    decButton_.SetParent(this);
    thumbButton_.SetParent(this);

    incButton_.SetIsSelectable(false);
    decButton_.SetIsSelectable(false);
    thumbButton_.SetIsSelectable(false);

    thumbButton_.SetReleasedColor(optor::color::ScrollBarThumb);

    SetBackgroundColor(optor::color::WindowBackground);
}

void optor::ScrollBar::Move(float shiftPercent) {
    const double newPercentage = std::clamp(percentage_ + shiftPercent, 0.f, 1.f);
    const double realShift = newPercentage - percentage_;
    percentage_ = (isHorizontal_ ? newPercentage : 1 - newPercentage);

    action_(percentage_);

    const dr4::Vec2f barSize = rect_.rect.size;
    dr4::Vec2f thumbPos = thumbButton_.GetPosition();

    if (isHorizontal_) {
        const double travel = barSize.x - 3.0 * buttonSize_.x;
        thumbPos.x = buttonSize_.x + percentage_ * travel;
    } else {
        const double travel = barSize.y - 3.0 * buttonSize_.y;
        thumbPos.y = buttonSize_.y + percentage_ * travel;
    }

    thumbButton_.SetPosition(thumbPos);
}

void optor::ScrollBar::Draw(dr4::Texture& srcTexture) {
    const dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    ERROR_HANDLE([this](){
        incButton_.Draw(*texture_);
    });

    ERROR_HANDLE([this](){
        decButton_.Draw(*texture_);
    });

    ERROR_HANDLE([this](){
        thumbButton_.Draw(*texture_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
    });
}

bool optor::ScrollBar::OnMouseMove(const dr4::Event& event) {
    const dr4::Vec2f mouse = event.mouseMove.pos;

    if (state_->draggedWidget == &thumbButton_) {
        const dr4::Vec2f barSize = rect_.rect.size;
        const dr4::Vec2f thumbSize = thumbButton_.GetSize();
        const dr4::Vec2f absBarPos = AbsCoord();

        double curPos;
        double maxTravel;

        if (isHorizontal_) {
            curPos = mouse.x - absBarPos.x - thumbSize.x;
            maxTravel = barSize.x - 2.0 * thumbSize.x;
        } else {
            curPos = barSize.y - (mouse.y - absBarPos.y) - thumbSize.y;
            maxTravel = barSize.y - 2.0 * thumbSize.y;
        }

        double newPercent = std::clamp(curPos / maxTravel, 0.0, 1.0);
        double shift = newPercent - percentage_;
        Move(shift);
    }

    
    if (Propagate(event, &optor::WidgetButton::OnMouseMove)) {
        return true;
    }

    return Widget::OnMouseMove(event);
}

bool optor::ScrollBar::OnMousePress(const dr4::Event& event) {

    if ((state_->hoveredWidget == this 
      || state_->hoveredWidget == &incButton_ 
      || state_->hoveredWidget == &decButton_
      || state_->hoveredWidget == &thumbButton_)
      && event.mouseButton.button == CONTROL_BUTTON_) 
    {
        state_->selectedWidget = this;
    }
    
    const bool childrenRes = Propagate(event, &optor::WidgetButton::OnMousePress);

    if (thumbButton_.IsPressed()) {
        state_->draggedWidget = &thumbButton_;
        return true;
    }
    
    if (childrenRes) {
        return true;
    }

    if (state_->hoveredWidget == this && event.mouseButton.button == CONTROL_BUTTON_) {
        if (isHorizontal_) {
            if (event.mouseButton.pos.x < AbsCoord().x + thumbButton_.GetPosition().x) {
                Move(-MIN_SHIFT_);
            } else {
                Move(MIN_SHIFT_);
            }
        } else {
            if (event.mouseButton.pos.y > AbsCoord().y + thumbButton_.GetPosition().y + thumbButton_.GetSize().y) {
                Move(-MIN_SHIFT_);
            } else {
                Move(MIN_SHIFT_);
            }
        }

        return true;
    }
    
    return Widget::OnMousePress(event);
}

bool optor::ScrollBar::OnMouseRelease(const dr4::Event& event) {
    const bool thumbWasPressed = thumbButton_.IsPressed();

    const bool childrenRes = Propagate(event, &optor::WidgetButton::OnMouseRelease);

    if (thumbWasPressed && !thumbButton_.IsPressed()) {
        state_->draggedWidget = nullptr;
        return true;
    }
    
    if (childrenRes) {
        return true;
    }
    
    return Widget::OnMouseRelease(event);
}

bool optor::ScrollBar::OnKeyboardPress(const dr4::Event& event) {
    if (event.key.sym == INC_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(MIN_SHIFT_);
        return true;
    }
    if (event.key.sym == DEC_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(-MIN_SHIFT_);
        return true;
    }
    if (event.key.sym == FULL_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(1.0 - percentage_);
        return true;
    }
    if (event.key.sym == ZERO_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(-percentage_);
        return true;
    }

    return Widget::OnKeyboardPress(event);
}

bool optor::ScrollBar::OnKeyboardRelease(const dr4::Event&) {
    return false;
}

void optor::ScrollBar::OnIdle() {
    if (incButton_.IsPressed()) Move( MIN_SHIFT_);
    if (decButton_.IsPressed()) Move(-MIN_SHIFT_);

    Widget::OnIdle();
}

bool optor::ScrollBar::Propagate(const dr4::Event& event, HandleButtonsT handler)
{
    if (ERROR_HANDLE([&](){return handler(incButton_,   event);})) { return true; }
    if (ERROR_HANDLE([&](){return handler(decButton_,   event);})) { return true; }
    if (ERROR_HANDLE([&](){return handler(thumbButton_, event);})) { return true; }

    return false;
}