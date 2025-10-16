#include <deque>
#include <cassert>

#include "widgets/WidgetChildable.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Widget.hpp"

optor::WidgetChildable::WidgetChildable(hui::RectangleShape rect, optor::WidgetsState* state)
    :   Widget{std::move(rect), state}, children_{}
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

bool optor::WidgetChildable::OnMouseMove(const hui::Event& event) {
    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (ERROR_HANDLE(&optor::Widget::OnMouseMove, *childIt, event)) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMouseMove(event);
    });
}

bool optor::WidgetChildable::OnMousePress(const hui::Event& event) {
    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (ERROR_HANDLE(&optor::Widget::OnMousePress, *childIt, event)) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMousePress(event); // FIXME remove copypast use func
    });
}

bool optor::WidgetChildable::OnMouseRelease(const hui::Event& event) {
    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (ERROR_HANDLE(&optor::Widget::OnMouseRelease, *childIt, event)) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMouseRelease(event);
    });
}

bool optor::WidgetChildable::OnKeyboardPress(const hui::Event& event) {
    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (ERROR_HANDLE(&optor::Widget::OnKeyboardPress, *childIt, event)) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnKeyboardPress(event);
    });
}

bool optor::WidgetChildable::OnKeyboardRelease(const hui::Event& event) {
    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (ERROR_HANDLE(&optor::Widget::OnKeyboardRelease, *childIt, event)) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnKeyboardRelease(event);
    });
}

void optor::WidgetChildable::OnIdle() {
    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        ERROR_HANDLE(&optor::Widget::OnIdle, *childIt);
    }

    ERROR_HANDLE([this](){
        optor::Widget::OnIdle();
    });
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