#include <algorithm>

#include "dr4/math/vec2.hpp"

#include "widgets/WidgetList.hpp"
#include "common/ErrorHandler.hpp"
#include "global/Global.hpp"

optor::WidgetList::WidgetList(optor::WidgetsState* state)
    :   optor::WidgetChildable({2 * INIT_WIDGET_BORDER_THICKNESS, 2 * INIT_WIDGET_BORDER_THICKNESS}, state)
{}

optor::Widget* optor::WidgetList::AddChild(std::unique_ptr<Widget> child)
{
    ERROR_HANDLE([this, &child](){
        children_.push_back(std::move(child));
    });
    auto* const childPtr = children_.back().get();
    childPtr->SetParent(this);
    childPtr->SetPosition(childPtr->GetPosition() + dr4::Vec2f{INIT_WIDGET_BORDER_THICKNESS, rect_->GetSize().y - INIT_WIDGET_BORDER_THICKNESS});
    // childPtr->SetOutlineThickness(0);

    const dr4::Vec2f size = rect_->GetSize();

    rect_->SetSize({
        std::max(size.x, childPtr->GetSize().x + 2*INIT_WIDGET_BORDER_THICKNESS),
        size.y + childPtr->GetSize().y
    });

    ERROR_HANDLE([this, &size](){
        texture_->SetSize(rect_->GetSize());
    });

    return childPtr;
}