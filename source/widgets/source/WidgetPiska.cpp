#include "widgets/WidgetPiska.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "global/Global.hpp"
#include "pp/canvas.hpp"
#include "widgets/Widget.hpp"
#include <memory>

optor::WidgetPiska::WidgetPiska(optor::WidgetsState* state)
    :   optor::Widget(state->window->GetSize() - 2 * dr4::Vec2f{10, 10}, state),
        texture_{state->window->CreateTexture()},
        tools_(state->piskaPlugin->CreateTools(this)),
        shapes_{},
        piskaState_(nullptr, nullptr),
        piskaTheme_{
            .shapeColor = optor::color::Red,
            .lineColor = optor::color::Blue,
            .textColor = optor::color::TextPrimary,
            .baseFontSize = 20,
            .handleColor = optor::color::Cyan
        }
{
    ERROR_HANDLE([this](){
        texture_->SetSize(state_->window->GetSize());
    });

    ERROR_HANDLE([this](){
        texture_->Clear({optor::color::Transparent});
    });

    ERROR_HANDLE([this](){
        texture_->SetZero({10, 10});
    });

    rect_->SetFillColor(optor::color::Transparent);
    rect_->SetBorderColor(optor::color::Red);
    rect_->SetBorderThickness(10);
}

void optor::WidgetPiska::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
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

    for (const auto& shape : shapes_) {
        ERROR_HANDLE([this, &shape](){
            shape.second->DrawOn(*texture_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

//TODO implement

bool optor::WidgetPiska::OnMouseMove(const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseMove.pos -= AbsCoord() + texture_->GetZero();

    if (piskaState_.selectedTool) {
        if (piskaState_.selectedTool->OnMouseMove(childEvent.mouseMove)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnMouseMove(childEvent.mouseMove)) {
            return true;
        }
    }

    return true;
}

bool optor::WidgetPiska::OnMousePress(const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseButton.pos -= AbsCoord() + texture_->GetZero();


    if (piskaState_.selectedTool) {
        if (piskaState_.selectedTool->OnMouseDown(childEvent.mouseButton)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnMouseDown(childEvent.mouseButton)) {
            return true;
        }
    }

    return true;
}

bool optor::WidgetPiska::OnMouseRelease(const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseButton.pos -= AbsCoord() + texture_->GetZero();

    if (piskaState_.selectedTool) {
        if (piskaState_.selectedTool->OnMouseUp(childEvent.mouseButton)) {
            return true;
        }
    }

    for (auto& shape : shapes_) {
        if (shape.second->OnMouseUp(childEvent.mouseButton)) {
            return true;
        }
    }

    return true;
}

bool optor::WidgetPiska::OnKeyboardPress(const dr4::Event& event) {
    if (isHide_) { return false; }

    if (event.key.sym == dr4::KeyCode::KEYCODE_ESCAPE) {
        SetMustRemoved(true);
        return true;
    }

    if (event.key.sym == dr4::KeyCode::KEYCODE_R) {
        if (piskaState_.selectedTool == tools_[0].get()) {
            piskaState_.selectedTool = nullptr;
        } else {
            piskaState_.selectedTool = tools_[0].get();
        }
        return true;
    }

    if (event.key.sym == dr4::KeyCode::KEYCODE_C) {
        if (piskaState_.selectedTool == tools_[1].get()) {
            piskaState_.selectedTool = nullptr;
        } else {
            piskaState_.selectedTool = tools_[1].get();
        }
        return true;
    }

    // if (event.key.sym == dr4::KeyCode::KEYCODE_C) {
    //     prims_.push_back(std::unique_ptr<hui::GeomPrim>(state_->piskaPlugin->CreateGeomPrim(2, state_->window)));
    //     return true;
    // }

    // if (event.key.sym == dr4::KeyCode::KEYCODE_A) {
    //     prims_.push_back(std::unique_ptr<hui::GeomPrim>(state_->piskaPlugin->CreateGeomPrim(3, state_->window)));
    //     return true;
    // }

    return true;
}

bool optor::WidgetPiska::OnKeyboardRelease(const dr4::Event& event) {
    if (isHide_) { return false; } 

    return true;
}

void optor::WidgetPiska::OnIdle() {
    if (isHide_) { return; }

}


pp::ControlsTheme optor::WidgetPiska::GetControlsTheme() const {
    return piskaTheme_;
}

pp::State* optor::WidgetPiska::GetState() {
    return &piskaState_;
}

size_t optor::WidgetPiska::AddShape(pp::Shape *shape) {
    static size_t shapeInd = 0;
    ++shapeInd;

    shapes_[shapeInd].reset(shape);

    // shapes_[shapeInd] = std::unique_ptr<pp::Shape>(shape);
    return shapeInd;
}

void optor::WidgetPiska::DelShape(size_t ind) {
    shapes_.erase(ind);
}

dr4::Window *optor::WidgetPiska::GetWindow() {
    return state_->window;
}