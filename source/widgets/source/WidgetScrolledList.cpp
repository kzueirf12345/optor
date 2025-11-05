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

optor::WidgetScrolledList::WidgetScrolledList(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state)
    :   optor::WidgetChildable(size, state, window),
        scrollbar_{std::make_unique<optor::ScrollBar>(
            window, 
            dr4::Vec2f{INIT_SCROLLBAR_WIDTH, size.y}, 
            state, 
            [this](float percentage){ return this->Scroll(percentage); },
            false
        )}
{
    ERROR_HANDLE([this](){
        scrollbar_->SetPosition({rect_.rect.size.x - INIT_SCROLLBAR_WIDTH, 0});
    });

    ERROR_HANDLE([this](){
        scrollbar_->SetParent(this);
    });
}

void optor::WidgetScrolledList::Scroll(float percentage) {
    const float maxSize = GetListSize();
    const float diffSize = rect_.rect.size.y - maxSize;
    baseOffset_ = diffSize * percentage;
}

void optor::WidgetScrolledList::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    for (const auto& child : children_) {
        pos = child->GetPosition();

        ERROR_HANDLE([this, &child, &pos](){
            child->SetPosition(pos + dr4::Vec2f{0, baseOffset_});
        });

        ERROR_HANDLE([this, &child](){
            child->Draw(*texture_);
        });

        ERROR_HANDLE([&child, &pos](){
            child->SetPosition(pos);
        });
    }

    ERROR_HANDLE([this](){
        scrollbar_->Draw(*texture_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
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


// static optor::WidgetChildable* CreateMoveOpticButtons(optor::WidgetChildable* parent, optor::WidgetsState* state) {
//     assert(manager);
//     assert(sceneWidget);

//     auto* moveOpticButtons = dynamic_cast<optor::WidgetChildable*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         parent, 
//         std::make_unique<optor::WidgetChildable>(
//             hui::Vector2d{750, 400},
//             state
//         )
//     ));

//     auto* leftButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         moveOpticButtons, 
//         std::make_unique<optor::WidgetButtonMoveOpticObj>(
//             hui::Vector2d{200, 100},
//             state,
//             "left",
//             state->selectedObj,
//             optor::MoveDirection::LEFT
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, leftButton, hui::Vector2d(50, 150));

//     auto* rightButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         moveOpticButtons, 
//         std::make_unique<optor::WidgetButtonMoveOpticObj>(
//             hui::Vector2d{200, 100},
//             state,
//             "right",
//             state->selectedObj,
//             optor::MoveDirection::RIGHT
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, rightButton, hui::Vector2d(250, 150));

//     auto* upButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         moveOpticButtons, 
//         std::make_unique<optor::WidgetButtonMoveOpticObj>(
//             hui::Vector2d{200, 100},
//             state,
//             "up",
//             state->selectedObj,
//             optor::MoveDirection::UP
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, upButton, hui::Vector2d(150, 45));

//     auto* downButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         moveOpticButtons, 
//         std::make_unique<optor::WidgetButtonMoveOpticObj>(
//             hui::Vector2d{200, 100},
//             state,
//             "down",
//             state->selectedObj,
//             optor::MoveDirection::DOWN
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, downButton, hui::Vector2d(150, 255));

//     auto* forwardButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         moveOpticButtons, 
//         std::make_unique<optor::WidgetButtonMoveOpticObj>(
//             hui::Vector2d{200, 100},
//             state,
//             "forward",
//             state->selectedObj,
//             optor::MoveDirection::FORWARD
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, forwardButton, hui::Vector2d(500, 100));

//         auto* backwordButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
//         &optor::WidgetChildable::AddChild, 
//         moveOpticButtons, 
//         std::make_unique<optor::WidgetButtonMoveOpticObj>(
//             hui::Vector2d{200, 100},
//             state,
//             "backword",
//             state->selectedObj,
//             optor::MoveDirection::BACKWARD
//         )
//     ));

//     ERROR_HANDLE(&optor::Widget::SetPosition, backwordButton, hui::Vector2d(500, 200));

//     return moveOpticButtons;
// }


/*!SECTION

    auto* cameraButtons = dynamic_cast<optor::WidgetChildable*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        manager->GetDesktop(), 
        std::make_unique<optor::WidgetChildable>(
            hui::Vector2d{750, 400},
            manager->GetState()
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, cameraButtons, hui::Vector2d(1350, 100));

    auto* leftButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "left",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::LEFT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, leftButton, hui::Vector2d(50, 150));

    auto* rightButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "right",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::RIGHT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, rightButton, hui::Vector2d(250, 150));

    auto* upButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "up",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::UP
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, upButton, hui::Vector2d(150, 45));

    auto* downButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "down",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::DOWN
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, downButton, hui::Vector2d(150, 255));

    auto* forwardButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "forward",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::FORWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, forwardButton, hui::Vector2d(500, 100));

        auto* backwordButton = dynamic_cast<optor::WidgetButtonCamera*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        cameraButtons, 
        std::make_unique<optor::WidgetButtonCamera>(
            hui::Vector2d{200, 100},
            manager->GetState(),
            "backword",
            &sceneWidget->GetCamera(),
            optor::MoveDirection::BACKWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, backwordButton, hui::Vector2d(500, 200));
*/