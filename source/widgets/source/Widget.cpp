#include <cassert>
#include <optional>

#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/mousecodes.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"

optor::Widget::Widget(const dr4::Vec2f& size, optor::WidgetsState* state)
    :   rect_{{{0, 0}, size}, optor::color::WindowBackground, INIT_WIDGET_BORDER_THICKNESS, optor::color::WindowBorder}, 
        parent_{nullptr}, 
        state_{state}, 
        isDraggable_{true}, 
        dragButton_{optor::INIT_DRAG_WINDOW_BUTTON_}, 
        isFreeDraggable_{false},
        isSelectable_{true}, 
        selectButton_{optor::INIT_SELECT_WINDOW_BUTTON_},
        unselectButton_{optor::INIT_UNSELECT_WINDOW_BUTTON_},
        mustRemoved_(false),
        name_{std::nullopt}
{}

void optor::Widget::Draw(dr4::Texture& srcTexture) {
    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(rect_);
    });
}

void optor::Widget::SetPosition(const dr4::Vec2f& position) {
    rect_.rect.pos = position;
}

void optor::Widget::SetBackgroundColor(const dr4::Color& color) {
    rect_.fill = color;
}

void optor::Widget::SetBorderColor(const dr4::Color& color) {
    rect_.borderColor = color;
}

void optor::Widget::SetOutlineThickness(double thickness) {
    rect_.borderThickness = thickness;
}

void optor::Widget::SetParent(optor::Widget* parent)  {
    parent_ = parent;
}

void optor::Widget::SetIsDraggable(const bool isDraggable)  {
    isDraggable_ = isDraggable;
}

void optor::Widget::SetIsFreeDraggable(const bool isFreeDraggable)  {
    isFreeDraggable_ = isFreeDraggable;
}

void optor::Widget::SetDragButton(dr4::MouseCode dragButton)  {
    dragButton_ = dragButton;
}

void optor::Widget::SetIsSelectable(const bool isSelectable)  {
    isSelectable_ = isSelectable;
}

void optor::Widget::SetSelectButton(dr4::MouseCode selectButton)  {
    selectButton_ = selectButton;
}

void optor::Widget::SetUnselectButton(dr4::KeyCode unselectButton)  {
    unselectButton_ = unselectButton;
}

void optor::Widget::SetMustRemoved (const bool mustRemoved) {
    mustRemoved_ = mustRemoved;
}

void optor::Widget::SetName (const std::string& name) {
    name_ = name;
}


dr4::Vec2f optor::Widget::AbsCoord() const {
    dr4::Vec2f absCoord = rect_.rect.pos;
    for (const auto* ancestor = parent_; ancestor != nullptr; ancestor = ancestor->parent_) {
        absCoord = absCoord + ancestor->rect_.rect.pos;
    }
    return std::move(absCoord);
}

dr4::Vec2f optor::Widget::GetSize() const {
    return rect_.rect.size;
}

dr4::Vec2f optor::Widget::GetPosition() const {
    return rect_.rect.pos;
}

optor::WidgetsState* optor::Widget::GetState() const {
    return state_;
}

dr4::Color optor::Widget::GetBackgroundColor () const {
    return rect_.fill;
}
dr4::Color optor::Widget::GetBorderColor     () const {
    return rect_.borderColor;
}
double     optor::Widget::GetOutlineThickness() const {
    return rect_.borderThickness;
}

optor::Widget* optor::Widget::GetParent() const {
    return parent_;
}

bool optor::Widget::GetIsDraggable           () const {
    return isDraggable_;
}
bool optor::Widget::GetIsFreeDraggable       () const {
    return isFreeDraggable_;
}
dr4::MouseCode optor::Widget::GetDragButton  () const {
    return dragButton_;
}
bool optor::Widget::GetIsSelectable          () const {
    return isSelectable_;
}
dr4::MouseCode optor::Widget::GetSelectButton() const {
    return selectButton_;
}
dr4::KeyCode optor::Widget::GetUnselectButton() const {
    return unselectButton_;
}
bool optor::Widget::GetMustRemoved() const {
    return mustRemoved_;
}

bool optor::Widget::OnMouseMove(const dr4::Event& event) {
    if (state_->draggedWidget == this) {
        ERROR_HANDLE(&optor::Widget::Drag, this, event.mouseMove.rel);
        return true;
    }

    if (dr4::Rect2f(AbsCoord(), rect_.rect.size).Contains(event.mouseMove.pos)) {
        state_->hoveredWidget = this;
        return true;
    }

    return false;
}

bool optor::Widget::OnMousePress(const dr4::Event& event) {
    if (IsInderectedHovered() 
     && isDraggable_ 
     && event.mouseButton.button == dragButton_) 
    {
        state_->draggedWidget = this;
        return true;
    };

    if (IsInderectedHovered() 
     && isSelectable_ 
     && event.mouseButton.button == selectButton_) 
    {
        state_->selectedWidget = this;
        return true;
    };

    return false;
}

bool optor::Widget::OnMouseRelease(const dr4::Event& event) {
    if (state_->draggedWidget == this
     && event.mouseButton.button == dragButton_) {
        state_->draggedWidget = nullptr;
        return true;
    };

    return false;
}

bool optor::Widget::OnKeyboardPress  (const dr4::Event& event) {
    if (state_->selectedWidget == this
     && event.key.sym == unselectButton_) {
        state_->selectedWidget = nullptr;
        return true;
    };

    return false;
}

bool optor::Widget::OnKeyboardRelease(const dr4::Event& event) {
    return false;
}

void optor::Widget::OnIdle() {
    
}

bool optor::Widget::OnMe(const dr4::Vec2f& absCoord) const {
    const dr4::Vec2f leftCorner  = AbsCoord();
    const dr4::Vec2f rightCorner = leftCorner + rect_.rect.size;

    return leftCorner.x <= absCoord.x && absCoord.x <= rightCorner.x 
        && leftCorner.y <= absCoord.y && absCoord.y <= rightCorner.y;
}

void optor::Widget::Drag(const dr4::Vec2f& shift) {
    rect_.rect.pos = rect_.rect.pos + shift;

    if (!isFreeDraggable_ && parent_) {
        rect_.rect.pos = rect_.rect.pos.Clamped({0, 0}, parent_->rect_.rect.size - rect_.rect.size);
    }
}

bool optor::Widget::IsInderectedHovered() const {
    for (const auto* curHovered = state_->hoveredWidget; curHovered != nullptr; curHovered = curHovered->parent_) {
        if (curHovered == this) {
            return true;
        }
    }

    return false;
}

std::optional<std::string> optor::Widget::GetName() const {
    return name_;
}