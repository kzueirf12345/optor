#include <deque>
#include <cassert>

#include "widgets/WidgetChildable.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Widget.hpp"

optor::WidgetChildable::WidgetChildable(hui::RectangleShape rect)
    :   Widget{std::move(rect)}, children_{}
{}

void optor::WidgetChildable::Draw(hui::Window* window) {
    assert(window);

    ERROR_HANDLE([this, window](){
        optor::Widget::Draw(window);
    });

    for (const auto& child : children_) {
        ERROR_HANDLE(&optor::Widget::Draw, child, window);
    }
}

optor::Widget* optor::WidgetChildable::AddChild(std::unique_ptr<Widget> child) {
    ERROR_HANDLE([this, &child](){
        children_.push_back(std::move(child));
    });
    auto* const childPtr = children_.back().get();
    childPtr->SetParent(this);
    return childPtr;
}

optor::Widget& optor::WidgetChildable::operator[](size_t ind) noexcept {
    assert(ind < children_.size());
    return *children_[ind].get();
}

const optor::Widget& optor::WidgetChildable::operator[](size_t ind) const noexcept {
    assert(ind < children_.size());
    return *children_[ind].get();
}