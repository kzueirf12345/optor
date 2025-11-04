#include "widgets/WidgetList.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/math/vec2.hpp"
#include "global/Global.hpp"
#include <algorithm>

optor::WidgetList::WidgetList(dr4::Window* window, optor::WidgetsState* state)
    :   optor::WidgetChildable({1, 1}, state, window)
{}

optor::Widget* optor::WidgetList::AddChild(std::unique_ptr<Widget> child)
{
    ERROR_HANDLE([this, &child](){
        children_.push_back(std::move(child));
    });
    auto* const childPtr = children_.back().get();
    childPtr->SetParent(this);
    childPtr->SetPosition(childPtr->GetPosition() + dr4::Vec2f{INIT_WIDGET_BORDER_THICKNESS, rect_.rect.size.y + INIT_WIDGET_BORDER_THICKNESS});
    childPtr->SetOutlineThickness(0);

    rect_.rect.size.x = std::max(rect_.rect.size.x, childPtr->GetSize().x + 2*INIT_WIDGET_BORDER_THICKNESS);
    rect_.rect.size.y += childPtr->GetSize().y + 2 * INIT_WIDGET_BORDER_THICKNESS;

    std::cerr << childPtr->GetSize().x << std::endl;

    ERROR_HANDLE([this](){
        texture_->SetSize(rect_.rect.size);
    });

    return childPtr;
}