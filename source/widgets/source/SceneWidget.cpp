#include <cassert>
#include <memory>

#include "widgets/SceneWidget.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "optics/AABB.hpp"
#include "optics/Camera.hpp"
#include "optics/OpticObj.hpp"
#include "optics/Scene.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::SceneWidget::SceneWidget(const dr4::Vec2f& size, 
                                optor::WidgetsState* state)
    :   optor::Widget{size, state},
        texture_{state->window->CreateTexture()},
        scene_{state->window, size}
{
    ERROR_HANDLE([this, size](){
        texture_->SetSize(size);
    });

    ERROR_HANDLE(&optor::Scene::Update, scene_);
}

void optor::SceneWidget::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

void optor::SceneWidget::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*scene_.GetImage());
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

bool optor::SceneWidget::OnMouseMove(const dr4::Event& event) {
    if (isHide_) { return false; }

    const dr4::Vec2f mouseCoord = event.mouseMove.pos;
    const dr4::Vec2f mouseOffset = (mouseCoord - state_->prevMouseCoord) * optor::CAMERA_ROTATE_SPEED;

    if (state_->selectedWidget == this) {
        ERROR_HANDLE(&optor::SceneWidget::RotateCamera, this, mouseOffset);
        return true;
    }

    if (ERROR_HANDLE([this, &event](){
            return optor::Widget::OnMouseMove(event);
        })
    ) {
        return true;
    }


    return false;
}

bool optor::SceneWidget::OnMousePress(const dr4::Event& event) {
    if (isHide_) { return false; }

    const dr4::Vec2f pixel = event.mouseButton.pos - AbsCoord();
    if (event.mouseButton.button == selectButton_) {
        auto* selectedObj = scene_.GetObjAtPixel({pixel.x, pixel.y});
        if (selectedObj) {
            state_->selectedObj = selectedObj;
        }
    }

    return optor::Widget::OnMousePress(event);
}

bool optor::SceneWidget::OnKeyboardPress(const dr4::Event& event) {
    if (isHide_) { return false; }

    if (state_->selectedWidget == this) {
        switch (event.key.sym) {
            case dr4::KeyCode::KEYCODE_W: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::FORWARD);
                return true;
            }

            case dr4::KeyCode::KEYCODE_S: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::BACKWARD);
                return true;
            }

            case dr4::KeyCode::KEYCODE_A: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::LEFT);
                return true;
            }

            case dr4::KeyCode::KEYCODE_D: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::RIGHT);
                return true;
            }

            case dr4::KeyCode::KEYCODE_SPACE: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::UP);
                return true;
            }

            case dr4::KeyCode::KEYCODE_LCONTROL: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::DOWN);
                return true;
            }

            default:
                break;
        }
    }

    if (ERROR_HANDLE([this, &event](){
            return optor::Widget::OnKeyboardPress(event);
        })
    ) {
        return true;
    }


    return false;
}

bool optor::SceneWidget::OnKeyboardRelease(const dr4::Event& event) {
    if (isHide_) { return false; }

    if (state_->selectedWidget == this) {
        if (event.key.sym == dr4::KeyCode::KEYCODE_W
         || event.key.sym == dr4::KeyCode::KEYCODE_S
         || event.key.sym == dr4::KeyCode::KEYCODE_A
         || event.key.sym == dr4::KeyCode::KEYCODE_D
         || event.key.sym == dr4::KeyCode::KEYCODE_SPACE
         || event.key.sym == dr4::KeyCode::KEYCODE_LCONTROL
        ) {
            ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::UNKNOWN);
            return true;
        }
    }

    if (ERROR_HANDLE([this, &event](){
            return optor::Widget::OnKeyboardRelease(event);
        })
    ) {
        return true;
    }

    return false;
}

void optor::SceneWidget::RotateCamera(const dr4::Vec2f& mouseOffset) {
    double speed = 0;
    optor::RotateDirection dir = optor::RotateDirection::RIGHT;

    if (mouseOffset.x > 0) {
        dir = optor::RotateDirection::LEFT, 
        speed = mouseOffset.x;
    } else {
        dir = optor::RotateDirection::RIGHT, 
        speed = -mouseOffset.x;
    }

    if (speed) {
        ERROR_HANDLE(&optor::Camera::Rotate, scene_.GetCamera(), dir, speed);
    }
    
    if (mouseOffset.y < 0) {
        dir = optor::RotateDirection::DOWN, 
        speed = -mouseOffset.y;
    } else {
        dir = optor::RotateDirection::UP, 
        speed = mouseOffset.y;
    }

    if (speed) {
        ERROR_HANDLE(&optor::Camera::Rotate, scene_.GetCamera(), dir, speed);
    }
}

void optor::SceneWidget::OnIdle() { 
    if (isHide_) { return ; }

    static optor::OpticObj* prevSelected = nullptr;
    
    ERROR_HANDLE([this](){
        optor::Widget::OnIdle();
    });

    if (state_->selectedObj != prevSelected) {
        if (prevSelected) {
            scene_.PopObj();
        }
        if (state_->selectedObj)
        {
            scene_.AddObj(std::make_unique<optor::AABB>(state_->selectedObj->GetAABB(), optor::materials::SELECTOR));
        }
        prevSelected = state_->selectedObj;
    }

    ERROR_HANDLE(&optor::Scene::Update, scene_); // TODO smart update

}

optor::OpticObj* optor::SceneWidget::AddObj(std::unique_ptr<optor::OpticObj> obj) {
    auto* objPtr = ERROR_HANDLE(&optor::Scene::AddObj, &scene_, std::move(obj));
    return objPtr;
}

const optor::Camera& optor::SceneWidget::GetCamera() const  { return scene_.GetCamera(); }
      optor::Camera& optor::SceneWidget::GetCamera()        { return scene_.GetCamera(); }
const optor::Scene&  optor::SceneWidget::GetScene()  const  { return scene_; }