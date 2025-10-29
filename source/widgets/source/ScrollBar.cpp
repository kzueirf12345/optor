#include <cassert>
#include <algorithm>
#include "widgets/ScrollBar.hpp"
#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"
#include "hui/Renderer.hpp"
#include "hui/Vector.hpp"
#include "widgets/WidgetButton.hpp"

optor::ScrollBar::ScrollBar(const hui::Vector2d& size, optor::WidgetsState* state, 
                            ActionT action, bool isHorizontal)
    : optor::Widget(size, state),
      action_{std::move(action)},
      isHorizontal_{isHorizontal},
      buttonSize_{        
        (isHorizontal_ ? BUTTON_SIZE_PERCENT_ : 1.0) * texture_.GetSize().x,
        (!isHorizontal_ ? BUTTON_SIZE_PERCENT_ : 1.0) * texture_.GetSize().y
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
      isPressedDec_{false},
      renderer_(size)
{
    SetIsDraggable(false);

    const hui::Vector2d fullSize = texture_.GetSize();

    if (isHorizontal_) {
        decButton_.SetPosition({0, 0});
        incButton_.SetPosition({fullSize.x - buttonSize_.x, 0});
        thumbButton_.SetPosition({buttonSize_.x, 0});
    } else {
        decButton_.SetPosition({0, fullSize.y - buttonSize_.y});
        incButton_.SetPosition({0, 0});
        thumbButton_.SetPosition({0, fullSize.y - 2 * buttonSize_.y});
    }

    incButton_.SetParent(this);
    decButton_.SetParent(this);
    thumbButton_.SetParent(this);

    incButton_.SetIsSelectable(false);
    decButton_.SetIsSelectable(false);
    thumbButton_.SetIsSelectable(false);

    thumbButton_.SetReleasedColor(optor::color::ScrollBarThumb);

    SetBackgroundColor(optor::color::Poison);
}

void optor::ScrollBar::Move(double shiftPercent) {
    const double newPercentage = std::clamp(percentage_ + shiftPercent, 0.0, 1.0);
    const double realShift = newPercentage - percentage_;
    percentage_ = newPercentage;

    action_(percentage_);

    const hui::Vector2d barSize = texture_.GetSize();
    hui::Vector2d thumbPos = thumbButton_.GetPosition();

    if (isHorizontal_) {
        const double travel = barSize.x - 3.0 * buttonSize_.x;
        thumbPos.x = buttonSize_.x + percentage_ * travel;
    } else {
        const double travel = barSize.y - 3.0 * buttonSize_.y;
        thumbPos.y = barSize.y - buttonSize_.y - percentage_ * travel;
    }

    thumbButton_.SetPosition(thumbPos);
}

void optor::ScrollBar::Draw(hui::Renderer* renderer) {
    assert(renderer);

    const hui::Vector2d pos = sprite_.GetPosition();

    sprite_.SetPosition({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(&renderer_);
    });
    sprite_.SetPosition(pos);

    ERROR_HANDLE([this](){
        incButton_.Draw(&renderer_);
        decButton_.Draw(&renderer_);
        thumbButton_.Draw(&renderer_);
    });

    ERROR_HANDLE([this](){
        renderer_.Display();
    });

    hui::Sprite sprite = ERROR_HANDLE([this](){
        return hui::Sprite(ERROR_HANDLE(&hui::Renderer::GetTexture, renderer_));
    });

    ERROR_HANDLE(&hui::Sprite::SetPosition, &sprite, pos);

    ERROR_HANDLE(&hui::Renderer::Draw, renderer, sprite);
}

bool optor::ScrollBar::OnMouseMove(const hui::Event& event) {
    const hui::Vector2d mouse = event.GetMouseShift();

    if (state_->draggedWidget == &thumbButton_) {
        const hui::Vector2d barSize = texture_.GetSize();
        const hui::Vector2d thumbSize = thumbButton_.GetSize();
        const hui::Vector2d absBarPos = AbsCoord();

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

bool optor::ScrollBar::OnMousePress(const hui::Event& event) {
    
    const bool childrenRes = Propagate(event, &optor::WidgetButton::OnMousePress);

    if (thumbButton_.IsPressed()) {
        state_->draggedWidget = &thumbButton_;
        return true;
    }
    
    if (childrenRes) {
        return true;
    }

    if (state_->hoveredWidget == this && event.GetMouseButton() == CONTROL_BUTTON_) {
        if (isHorizontal_) {
            if (event.GetMouseCoord().x < AbsCoord().x + thumbButton_.GetPosition().x) {
                Move(-MIN_SHIFT_);
            } else {
                Move(MIN_SHIFT_);
            }
        } else {
            if (event.GetMouseCoord().y > AbsCoord().y + thumbButton_.GetPosition().y + thumbButton_.GetSize().y) {
                Move(-MIN_SHIFT_);
            } else {
                Move(MIN_SHIFT_);
            }
        }

        return true;
    }
    
    return Widget::OnMousePress(event);
}

bool optor::ScrollBar::OnMouseRelease(const hui::Event& event) {
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

bool optor::ScrollBar::OnKeyboardPress(const hui::Event& event) {
    if (event.GetKeyboardButton() == INC_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(MIN_SHIFT_);
        return true;
    }
    if (event.GetKeyboardButton() == DEC_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(-MIN_SHIFT_);
        return true;
    }
    if (event.GetKeyboardButton() == FULL_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(1.0 - percentage_);
        return true;
    }
    if (event.GetKeyboardButton() == ZERO_KEYBOARD_BUTTON_ && state_->selectedWidget == this) {
        Move(-percentage_);
        return true;
    }

    return Widget::OnKeyboardPress(event);
}

bool optor::ScrollBar::OnKeyboardRelease(const hui::Event&) {
    return false;
}

void optor::ScrollBar::OnIdle() {
    if (incButton_.IsPressed()) Move( MIN_SHIFT_);
    if (decButton_.IsPressed()) Move(-MIN_SHIFT_);

    Widget::OnIdle();
}

bool optor::ScrollBar::Propagate(const hui::Event& event, HandleButtonsT handler)
{
    if (ERROR_HANDLE([&](){return handler(incButton_,   event);})) { return true; }
    if (ERROR_HANDLE([&](){return handler(decButton_,   event);})) { return true; }
    if (ERROR_HANDLE([&](){return handler(thumbButton_, event);})) { return true; }

    return false;
}