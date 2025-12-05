#include <memory>
#include <cassert>

#include "common/ErrorHandler.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "global/Global.hpp"
#include "widgets/ScrollBar.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/WidgetScrolledList.hpp"

// static optor::WidgetChildable* CreateMoveOpticButtons(optor::WidgetChildable* parent, optor::WidgetsState* state);

optor::WidgetScrolledList::WidgetScrolledList(const dr4::Vec2f& size, optor::WidgetsState* state)
    :   optor::WidgetChildable(size, state),
        scrollbar_{std::make_unique<optor::ScrollBar>(
            dr4::Vec2f{INIT_SCROLLBAR_WIDTH, size.y}, 
            state, 
            [this](float percentage){ return this->Scroll(percentage); },
            false
        )},
        startPoses_()
{
    ERROR_HANDLE([this](){
        scrollbar_->SetPosition({rect_->GetSize().x - INIT_SCROLLBAR_WIDTH, 0});
    });

    ERROR_HANDLE([this](){
        scrollbar_->SetParent(this);
    });
}

void optor::WidgetScrolledList::Scroll(float percentage) {
    const float maxSize = GetListSize();
    const float diffSize = rect_->GetSize().y - maxSize;
    baseOffset_ = diffSize * percentage;
}

void optor::WidgetScrolledList::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    for (size_t childInd = 0; childInd < children_.size(); ++childInd) {
        const auto& child = children_[childInd];
        pos = startPoses_[childInd];

        ERROR_HANDLE([this, &child, &pos](){
            child->SetPosition(pos + dr4::Vec2f{0, baseOffset_});
        });

        ERROR_HANDLE([this, &child](){
            child->Draw(*texture_);
        });
    }

    ERROR_HANDLE([this](){
        scrollbar_->Draw(*texture_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

optor::Widget* optor::WidgetScrolledList::AddChild(std::unique_ptr<Widget> child)
{
    ERROR_HANDLE([this, &child](){
        children_.push_back(std::move(child));
    });
    auto* const childPtr = children_.back().get();
    childPtr->SetParent(this);
    childPtr->SetPosition(
        childPtr->GetPosition() + 
        dr4::Vec2f{
            INIT_WIDGET_BORDER_THICKNESS, 
            GetListSize() - childPtr->GetSize().y + INIT_WIDGET_BORDER_THICKNESS
        }
    );
    childPtr->SetOutlineThickness(0);
    childPtr->SetIsDraggable(false);
    startPoses_.push_back(childPtr->GetPosition());

    return childPtr;
}

float optor::WidgetScrolledList::GetListSize() const {
    float sum = 0;

    for (const auto& child : children_) {
        sum += child->GetSize().y;
    }

    return sum;
}

bool optor::WidgetScrolledList::OnMouseMove      (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
        return scrollbar_->OnMouseMove(event);
    })) {
        return true;
    }

    return ERROR_HANDLE([this, &event](){
        return optor::WidgetChildable::OnMouseMove(event);
    });
}

bool optor::WidgetScrolledList::OnMousePress     (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
        return scrollbar_->OnMousePress(event);
    })) {
        return true;
    }

    return ERROR_HANDLE([this, &event](){
        return optor::WidgetChildable::OnMousePress(event);
    });
}

bool optor::WidgetScrolledList::OnMouseRelease   (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
        return scrollbar_->OnMouseRelease(event);
    })) {
        return true;
    }

    return ERROR_HANDLE([this, &event](){
        return optor::WidgetChildable::OnMouseRelease(event);
    });
}

bool optor::WidgetScrolledList::OnKeyboardPress  (const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
        return scrollbar_->OnKeyboardPress(event);
    })) {
        return true;
    }

    return ERROR_HANDLE([this, &event](){
        return optor::WidgetChildable::OnKeyboardPress(event);
    });
}

bool optor::WidgetScrolledList::OnKeyboardRelease(const dr4::Event& event) 
{
    if (isHide_) { return false; }

    if (ERROR_HANDLE([this, &event](){
        return scrollbar_->OnKeyboardRelease(event);
    })) {
        return true;
    }

    return ERROR_HANDLE([this, &event](){
        return optor::WidgetChildable::OnKeyboardRelease(event);
    });
}

void optor::WidgetScrolledList::OnIdle()                        
{
    if (isHide_) { return; }

    ERROR_HANDLE([this](){
        scrollbar_->OnIdle();
    });

    ERROR_HANDLE([this](){
        optor::WidgetChildable::OnIdle();
    });
}