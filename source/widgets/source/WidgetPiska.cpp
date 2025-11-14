#include "widgets/WidgetPiska.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "global/Global.hpp"
#include "hui/geomprim.hpp"
#include "widgets/Widget.hpp"
#include <memory>

optor::WidgetPiska::WidgetPiska(optor::WidgetsState* state)
    :   optor::Widget(state->window->GetSize() - 2 * dr4::Vec2f{10, 10}, state),
        texture_{state->window->CreateTexture()},
        prims_{}
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

void optor::WidgetPiska::Draw       (dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    texture_->Clear(optor::color::Transparent);

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    for (const auto& prim : prims_) {
        ERROR_HANDLE([this, &prim](){
            prim->DrawOn(*texture_);
        });
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}


bool optor::WidgetPiska::OnMouseMove      (const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseMove.pos -= AbsCoord() + texture_->GetZero();

    for (auto& prim : prims_) {
        if (prim->OnMouseMove(childEvent)) {
            return true;
        }
    }

    return true;
}

bool optor::WidgetPiska::OnMousePress     (const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseButton.pos -= AbsCoord() + texture_->GetZero();

    for (auto& prim : prims_) {
        if (prim->OnMouseDown(childEvent)) {
            return true;
        }
    }

    return true;
}

bool optor::WidgetPiska::OnMouseRelease   (const dr4::Event& event) {
    if (isHide_) { return false; }

    dr4::Event childEvent(event);
    childEvent.mouseButton.pos -= AbsCoord() + texture_->GetZero();

    for (auto& prim : prims_) {
        if (prim->OnMouseRelease(childEvent)) {
            return true;
        }
    }

    return true;
}

bool optor::WidgetPiska::OnKeyboardPress  (const dr4::Event& event) {
    if (isHide_) { return false; }

    if (event.key.sym == dr4::KeyCode::KEYCODE_ESCAPE) {
        SetMustRemoved(true);
        return true;
    }

    if (event.key.sym == dr4::KeyCode::KEYCODE_R) {
        prims_.push_back(std::unique_ptr<hui::GeomPrim>(state_->geomPrimBackend->CreateGeomPrim(1, state_->window)));
        return true;
    }

    if (event.key.sym == dr4::KeyCode::KEYCODE_C) {
        prims_.push_back(std::unique_ptr<hui::GeomPrim>(state_->geomPrimBackend->CreateGeomPrim(2, state_->window)));
        return true;
    }

    if (event.key.sym == dr4::KeyCode::KEYCODE_A) {
        prims_.push_back(std::unique_ptr<hui::GeomPrim>(state_->geomPrimBackend->CreateGeomPrim(3, state_->window)));
        return true;
    }

    return true;
}

bool optor::WidgetPiska::OnKeyboardRelease(const dr4::Event& event) {
    if (isHide_) { return false; } 

    return true;
}

void optor::WidgetPiska::OnIdle           () {
    if (isHide_) { return; }

}
