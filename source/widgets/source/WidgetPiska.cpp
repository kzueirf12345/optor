#include "widgets/WidgetPiska.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/mouse_buttons.hpp"
#include "global/Global.hpp"
#include "pp/canvas.hpp"
#include "widgets/ColorPicker.hpp"
#include "widgets/PiskaToolButton.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetScrolledList.hpp"
#include <cassert>
#include <memory>

optor::WidgetPiska::WidgetPiska(optor::WidgetsState* state)
    :   optor::WidgetChildable(state->window->GetSize(), state),
        tools_(),
        shapes_{},
        piskaTheme_{
            .shapeFillColor = optor::color::Transparent,
            .shapeBorderColor = optor::color::Red,
            .selectColor = optor::color::Poison,
            .textColor = optor::color::TextPrimary,
            .baseFontSize = 20,
            .handleColor = optor::color::Cyan,
            .handleHoverColor = optor::color::Cyan, 
            .handleActiveColor = optor::color::Cyan
        },
        selectedTool_{nullptr},
        selectedShape_{nullptr}
{
    ERROR_HANDLE([this](){
        texture_->Clear({optor::color::Transparent});
    });

    ERROR_HANDLE([this](){
        texture_->SetZero({10, 10});
    });

    rect_->SetSize(state_->window->GetSize() - dr4::Vec2f(20, 20));
    rect_->SetFillColor(optor::color::Transparent);
    rect_->SetBorderColor(optor::color::Red);
    rect_->SetBorderThickness(10);

    for (auto* plugin : state->piskaPlugins)
    {
        for (auto& tool : plugin->CreateTools(this)) 
        {
            tools_.push_back(std::move(tool));
        }
    }

    const float listMargin = 100;
    const float listWidth = 300;

    auto* list = dynamic_cast<optor::WidgetScrolledList*>(AddChild(std::make_unique<optor::WidgetScrolledList>(
        dr4::Vec2f{listWidth + INIT_SCROLLBAR_WIDTH, state_->window->GetSize().y - 2 *listMargin},
        state_
    )));

    list->SetPosition({0, listMargin});


    for (auto& tool : tools_) {
        auto* button = list->AddChild(std::make_unique<optor::PiskaToolButton>(
            dr4::Vec2f(listWidth, 100),
            state_,
            tool.get(),
            &selectedTool_
        ));
    }

    auto* colorPicker = dynamic_cast<optor::ColorPicker*>(AddChild(std::make_unique<optor::ColorPicker>(
        dr4::Vec2f(400, 300), state_, &piskaTheme_
    )));
    colorPicker->SetPosition({listWidth, 0});
}

void optor::WidgetPiska::SetPosition(const dr4::Vec2f& position) {
    optor::WidgetChildable::SetPosition(position);
    texture_->SetPos(position);
}

void optor::WidgetPiska::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    texture_->Clear(optor::color::Transparent);

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

    for (const auto& shape : shapes_) {
        ERROR_HANDLE([this, &shape](){
            shape.second->DrawOn(*texture_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

bool optor::WidgetPiska::OnMouseMove(const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseMove.pos -= AbsCoord() + texture_->GetZero();

    if (selectedTool_) {
        if (selectedTool_->OnMouseMove(childEvent.mouseMove)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnMouseMove(childEvent.mouseMove)) {
            return true;
        }
    }

    optor::WidgetChildable::OnMouseMove(event);

    return true;
}

bool optor::WidgetPiska::OnMousePress(const dr4::Event& event) {
    if (isHide_) { return false; }

    for (auto childIt = children_.rbegin(); childIt != children_.rend(); ++childIt) {
        if (!(*childIt)->GetMustRemoved() && ERROR_HANDLE([childIt, &event](){
                return (*childIt)->OnMousePress(event);
        })) {
            return true;
        }
    }

    dr4::Event childEvent(event);
    childEvent.mouseButton.pos -= AbsCoord() + texture_->GetZero();


    if (selectedTool_) {
        if (selectedTool_->OnMouseDown(childEvent.mouseButton)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnMouseDown(childEvent.mouseButton)) {
            return true;
        }
    }

    if (event.mouseButton.button == dr4::MouseButtonType::LEFT) {
        SetSelectedShape(nullptr);
    }

    return true;
}

bool optor::WidgetPiska::OnMouseRelease(const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseButton.pos -= AbsCoord() + texture_->GetZero();

    if (selectedTool_) {
        if (selectedTool_->OnMouseUp(childEvent.mouseButton)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnMouseUp(childEvent.mouseButton)) {
            return true;
        }
    }

    if (optor::WidgetChildable::OnMouseRelease(event)) {
        return true;
    }

    return true;
}

bool optor::WidgetPiska::OnKeyboardPress(const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);

    if (selectedTool_) {
        if (selectedTool_->OnKeyDown(childEvent.key)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnKeyDown(childEvent.key)) {
            return true;
        }
    }

    if (event.key.sym == dr4::KeyCode::KEYCODE_ESCAPE) {
        SetMustRemoved(true);
        return true;
    }

    optor::WidgetChildable::OnKeyboardPress(event);

    return true;
}

bool optor::WidgetPiska::OnKeyboardRelease(const dr4::Event& event) {
    if (isHide_) { return false; } 

    dr4::Event childEvent(event);

    if (selectedTool_) {
        if (selectedTool_->OnKeyUp(childEvent.key)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnKeyUp(childEvent.key)) {
            return true;
        }
    }

    optor::WidgetChildable::OnKeyboardRelease(event);

    return true;
}

bool optor::WidgetPiska::OnTextInput(const dr4::Event& event) {
    if (isHide_) { return false; } 

    dr4::Event childEvent(event);

    if (selectedTool_) {
        if (selectedTool_->OnText(childEvent.text)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnText(childEvent.text)) {
            return true;
        }
    }

    optor::WidgetChildable::OnTextInput(event);

    return true;
}

void optor::WidgetPiska::OnIdle() {
    if (isHide_) { return; }

    optor::WidgetChildable::OnIdle();
}


pp::ControlsTheme optor::WidgetPiska::GetControlsTheme() const {
    return piskaTheme_;
}

void optor::WidgetPiska::AddShape(pp::Shape *shape) {
    assert(shape);

    shapes_[shape].reset(shape);
}

void optor::WidgetPiska::DelShape(pp::Shape *shape) {
    assert(shape);

    ERROR_HANDLE([this, shape]() {
        shapes_.erase(shape);
    });
}

void optor::WidgetPiska::SetSelectedShape(pp::Shape *shape) {
    selectedShape_ = shape;
}

pp::Shape *optor::WidgetPiska::GetSelectedShape() const {
    return selectedShape_;
}

void optor::WidgetPiska::ShapeChanged(pp::Shape *shape) {
    // TODO chto eto
}

dr4::Window *optor::WidgetPiska::GetWindow() {
    return state_->window;
}

