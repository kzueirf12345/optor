#include <cassert>

#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Drawable.hpp"
#include "hui/RectangleShape.hpp"
#include "hui/Vector.hpp"
#include "global/Global.hpp"

optor::Widget::Widget(hui::RectangleShape rect)
    :   rect_{std::move(rect)}, parent_{nullptr}
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

hui::Vector2d optor::Widget::AbsCoord() const {
    hui::Vector2d absCoord = rect_.GetPosition();
    for (const auto* ancestor = parent_; ancestor != nullptr; ancestor = ancestor->parent_) {
        absCoord += ancestor->rect_.GetPosition();
    }
    return std::move(absCoord);
}