#include <deque>
#include <cassert>
#include <memory>

#include "widgets/WidgetChildable.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/event.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "widgets/Widget.hpp"

optor::WidgetChildable::WidgetChildable(const dr4::Vec2f& size, optor::WidgetsState* state)
    :   Widget{size, state}, children_{}, texture_{state->window->CreateTexture()}
{
    ERROR_HANDLE([this, size](){
        texture_->SetSize(size);
    });
}

void optor::WidgetChildable::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

void optor::WidgetChildable::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    for (const auto& child : children_) {
        ERROR_HANDLE([this, &child](){
            child->Draw(*texture_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}


bool optor::WidgetChildable::OnMouseMove(const dr4::Event& event) {
    if (isHide_) { return false; }

    bool res = ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMouseMove(event);
    });

    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (!(*childIt)->GetMustRemoved() && ERROR_HANDLE([childIt, &event](){
                return (*childIt)->OnMouseMove(event);
        })) {
            return true;
        }
    }

    return res;
}

bool optor::WidgetChildable::OnMousePress(const dr4::Event& event) {
    if (isHide_) { return false; }

    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (!(*childIt)->GetMustRemoved() && ERROR_HANDLE([childIt, &event](){
                return (*childIt)->OnMousePress(event);
        })) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMousePress(event);
    });
}

bool optor::WidgetChildable::OnMouseRelease(const dr4::Event& event) {
    if (isHide_) { return false; }

    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (!(*childIt)->GetMustRemoved() && ERROR_HANDLE([childIt, &event](){
                return (*childIt)->OnMouseRelease(event);
        })) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnMouseRelease(event);
    });
}

bool optor::WidgetChildable::OnKeyboardPress(const dr4::Event& event) {
    if (isHide_) { return false; }

    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (!(*childIt)->GetMustRemoved() && ERROR_HANDLE([childIt, &event](){
                return (*childIt)->OnKeyboardPress(event);
        })) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnKeyboardPress(event);
    });
}

bool optor::WidgetChildable::OnKeyboardRelease(const dr4::Event& event) {
    if (isHide_) { return false; }

    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (!(*childIt)->GetMustRemoved() && ERROR_HANDLE([childIt, &event](){
                return (*childIt)->OnKeyboardRelease(event);
        })) {
            return true;
        }
    }

    return ERROR_HANDLE([this, &event](){
        return optor::Widget::OnKeyboardRelease(event);
    });
}

void optor::WidgetChildable::OnIdle() {
    if (isHide_) { return; }

    children_.erase(
        std::remove_if(children_.begin(), children_.end(),
            [](const std::unique_ptr<Widget>& child) {
                return child->GetMustRemoved();
            }),
        children_.end()
    );

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

optor::Widget* optor::WidgetChildable::GetChild(size_t ind) const {
    assert(ind < children_.size());
    return children_[ind].get();
}

size_t optor::WidgetChildable::GetChildrenCount() const {
    return children_.size();
}

bool optor::WidgetChildable::IsInderectedHovered() const {
    if (isHide_) { return false; }

    for (const auto& child : children_) {
        if (child->IsInderectedHovered()) {
            return true;
        }
    }

    return optor::Widget::IsInderectedHovered();
}