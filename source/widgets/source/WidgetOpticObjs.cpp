#include <memory>
#include <cassert>

#include "common/ErrorHandler.hpp"
#include "widgets/WidgetOpticObjs.hpp"
#include "global/Global.hpp"
#include "hui/Vector.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/WidgetButtonCamera.hpp"
#include "widgets/WidgetButtonMoveOpticObj.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetManager.hpp"
#include "widgets/WidgetOpticObj.hpp"

static optor::WidgetChildable* CreateMoveOpticButtons(optor::WidgetChildable* parent, optor::WidgetsState* state);

optor::WidgetOpticObjs::WidgetOpticObjs(const hui::Vector2d& size, optor::WidgetsState* state, 
                                        const optor::Scene& scene)
    :   optor::WidgetChildable(size, state)
{
    const auto& objs = scene.GetObjs();
    for (auto obj = objs.begin(); obj != objs.end(); ++obj) {
        auto* child = dynamic_cast<optor::WidgetOpticObj*>(ERROR_HANDLE([&](){
            return this->AddChild(std::make_unique<optor::WidgetOpticObj>(
                hui::Vector2d{size.x, optor::STRING_BLOCK_HEIGHT}, 
                state, 
                obj->get()
            ));
        }));
        
        const size_t ind = obj - objs.begin();

        child->SetPosition(hui::Vector2d{0, optor::STRING_BLOCK_HEIGHT * ind});
    }

    auto* buttons = CreateMoveOpticButtons(this, state_);

    buttons->SetPosition(hui::Vector2d{0, optor::STRING_BLOCK_HEIGHT * (children_.size() - 1)});
}

void optor::WidgetOpticObjs::Scroll(double percentage) {
    const double maxSize = (children_.size() - 1) * optor::STRING_BLOCK_HEIGHT + children_.back()->GetSize().y;
    const double diffSize = texture_.GetSize().y - maxSize;
    const double baseOffset = diffSize * percentage;

    for (size_t ind = 0; ind < children_.size(); ++ind) {
        auto* child = children_[ind].get();
        child->SetPosition(hui::Vector2d{0, baseOffset + optor::STRING_BLOCK_HEIGHT * ind});
    }
}

void optor::WidgetOpticObjs::Draw(hui::Renderer* renderer) {
    assert(renderer);

    const hui::Vector2d pos = sprite_.GetPosition();

    sprite_.SetPosition({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(&renderer_);
    });
    sprite_.SetPosition(pos);

    for (const auto& child : children_) {
        ERROR_HANDLE([this, &child](){
            child->Draw(&renderer_);
        });
    }

    ERROR_HANDLE([this](){
        renderer_.Display();
    });
    
    hui::Sprite sprite = ERROR_HANDLE([this](){
        return hui::Sprite(ERROR_HANDLE(&hui::Renderer::GetTexture, renderer_));
    });
    sprite.SetPosition(pos);

    ERROR_HANDLE([renderer, &sprite](){
        renderer->Draw(sprite);
    });
}

static optor::WidgetChildable* CreateMoveOpticButtons(optor::WidgetChildable* parent, optor::WidgetsState* state) {
    assert(manager);
    assert(sceneWidget);

    auto* moveOpticButtons = dynamic_cast<optor::WidgetChildable*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        parent, 
        std::make_unique<optor::WidgetChildable>(
            hui::Vector2d{750, 400},
            state
        )
    ));

    auto* leftButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        moveOpticButtons, 
        std::make_unique<optor::WidgetButtonMoveOpticObj>(
            hui::Vector2d{200, 100},
            state,
            "left",
            state->selectedObj,
            optor::MoveDirection::LEFT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, leftButton, hui::Vector2d(50, 150));

    auto* rightButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        moveOpticButtons, 
        std::make_unique<optor::WidgetButtonMoveOpticObj>(
            hui::Vector2d{200, 100},
            state,
            "right",
            state->selectedObj,
            optor::MoveDirection::RIGHT
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, rightButton, hui::Vector2d(250, 150));

    auto* upButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        moveOpticButtons, 
        std::make_unique<optor::WidgetButtonMoveOpticObj>(
            hui::Vector2d{200, 100},
            state,
            "up",
            state->selectedObj,
            optor::MoveDirection::UP
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, upButton, hui::Vector2d(150, 45));

    auto* downButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        moveOpticButtons, 
        std::make_unique<optor::WidgetButtonMoveOpticObj>(
            hui::Vector2d{200, 100},
            state,
            "down",
            state->selectedObj,
            optor::MoveDirection::DOWN
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, downButton, hui::Vector2d(150, 255));

    auto* forwardButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        moveOpticButtons, 
        std::make_unique<optor::WidgetButtonMoveOpticObj>(
            hui::Vector2d{200, 100},
            state,
            "forward",
            state->selectedObj,
            optor::MoveDirection::FORWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, forwardButton, hui::Vector2d(500, 100));

        auto* backwordButton = dynamic_cast<optor::WidgetButtonMoveOpticObj*>(ERROR_HANDLE(
        &optor::WidgetChildable::AddChild, 
        moveOpticButtons, 
        std::make_unique<optor::WidgetButtonMoveOpticObj>(
            hui::Vector2d{200, 100},
            state,
            "backword",
            state->selectedObj,
            optor::MoveDirection::BACKWARD
        )
    ));

    ERROR_HANDLE(&optor::Widget::SetPosition, backwordButton, hui::Vector2d(500, 200));

    return moveOpticButtons;
}


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