#include <cassert>

#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "global/Global.hpp"

optor::Widget::Widget(hui::RectangleShape rect, optor::WidgetsState* state)
    :   rect_{std::move(rect)}, 
        parent_{nullptr}, 
        state_{state}, 
        isDraggable_{true}, 
        dragButton_{optor::INIT_DRAG_WINDOW_BUTTON_}, 
        isFreeDraggable_{false},
        isSelectable_{true}, 
        selectButton_{optor::INIT_SELECT_WINDOW_BUTTON_}
{
    ERROR_HANDLE(&hui::RectangleShape::SetFillColor,        &rect_, optor::color::WindowBackground);
    ERROR_HANDLE(&hui::RectangleShape::SetOutlineColor,     &rect_, optor::color::WindowBorder);
    ERROR_HANDLE(&hui::RectangleShape::SetOutlineThickness, &rect_, optor::INIT_WIDGET_BORDER_THICKNESS);
}

void optor::Widget::Draw(hui::Window* window) {
    assert(window);

    const hui::Vector2d relCoord = rect_.GetPosition();
    ERROR_HANDLE(&hui::RectangleShape::SetPosition, &rect_, std::move(AbsCoord()));

    ERROR_HANDLE([window, this](){
        window->Draw(rect_);
    });

    ERROR_HANDLE(&hui::RectangleShape::SetPosition, &rect_, relCoord);
}

void optor::Widget::SetPosition(const hui::Vector2d& position) {
    ERROR_HANDLE(&hui::RectangleShape::SetPosition, &rect_, position);
}

void optor::Widget::SetBackgroundColor(const hui::Color& color) {
    ERROR_HANDLE(&hui::RectangleShape::SetFillColor, &rect_, color);
}

void optor::Widget::SetBorderColor(const hui::Color& color) {
    ERROR_HANDLE(&hui::RectangleShape::SetOutlineColor, &rect_, color);
}

void optor::Widget::SetOutlineThickness(double thickness) {
    ERROR_HANDLE(&hui::RectangleShape::SetOutlineThickness, &rect_, thickness);
}

void optor::Widget::SetParent(optor::Widget* parent) noexcept {
    parent_ = parent;
}

void optor::Widget::SetIsDraggable(const bool isDraggable) noexcept {
    isDraggable_ = isDraggable;
}

void optor::Widget::SetIsFreeDraggable(const bool isFreeDraggable) noexcept {
    isFreeDraggable_ = isFreeDraggable;
}

void optor::Widget::SetDragButton(hui::Event::MouseButton dragButton) noexcept {
    dragButton_ = dragButton;
}

void optor::Widget::SetIsSelectable(const bool isSelectable) noexcept {
    isSelectable_ = isSelectable;
}

void optor::Widget::SetSelectButton(hui::Event::MouseButton selectButton) noexcept {
    selectButton_ = selectButton;
}


hui::Vector2d optor::Widget::AbsCoord() const {
    hui::Vector2d absCoord = rect_.GetPosition();
    for (const auto* ancestor = parent_; ancestor != nullptr; ancestor = ancestor->parent_) {
        absCoord += ancestor->rect_.GetPosition();
    }
    return std::move(absCoord);
}

hui::Vector2d optor::Widget::GetSize() const {
    return ERROR_HANDLE(&hui::RectangleShape::GetSize, rect_);
}

bool optor::Widget::OnMouseMove(const hui::Event& event) {
    const hui::Vector2d mouseCoord = event.GetMouseCoord();

    if (state_->draggedWidget == this) {
        ERROR_HANDLE(&optor::Widget::Drag, this, mouseCoord - state_->prevMouseCoord);
        return true;
    }

    if (ERROR_HANDLE(&optor::Widget::OnMe, this, mouseCoord)) {
        state_->hoveredWidget = this;
        return true;
    }

    return false;
}

bool optor::Widget::OnMousePress(const hui::Event& event) {
    if (state_->hoveredWidget == this 
     && isDraggable_ 
     && event.GetMouseButton() == dragButton_) {
        state_->draggedWidget = this;
        return true;
    };

    if (state_->hoveredWidget == this 
     && isSelectable_ 
     && event.GetMouseButton() == selectButton_) {
        state_->selectedWidget = this;
        return true;
    };

    return false;
}

bool optor::Widget::OnMouseRelease(const hui::Event& event) {
    if (state_->draggedWidget == this
     && event.GetMouseButton() == dragButton_) {
        state_->draggedWidget = nullptr;
        return true;
    };

    return false;
}

void optor::Widget::OnIdle() {
    
}

bool optor::Widget::OnMe(const hui::Vector2d& absCoord) const {
    const hui::Vector2d leftCorner  = AbsCoord();
    const hui::Vector2d rightCorner = leftCorner + rect_.GetSize();

    return leftCorner.x <= absCoord.x && absCoord.x <= rightCorner.x 
        && leftCorner.y <= absCoord.y && absCoord.y <= rightCorner.y;
}

void optor::Widget::Drag(const hui::Vector2d& shift) {
    ERROR_HANDLE(&hui::RectangleShape::SetPosition, &rect_, rect_.GetPosition() + shift);

    if (!isFreeDraggable_ && parent_){
        ERROR_HANDLE(
            &hui::RectangleShape::SetPosition, 
            &rect_, 
            rect_.GetPosition().Clump(
                {0, 0},
                parent_->rect_.GetSize() - rect_.GetSize()
            )
        );
    }
}