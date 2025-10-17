#include "widgets/SceneWidget.hpp"
#include "hui/Event.hpp"
#include "hui/Renderer.hpp"
#include "hui/Sprite.hpp"
#include "hui/Vector.hpp"
#include "optics/Camera.hpp"
#include "optics/Scene.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::SceneWidget::SceneWidget(hui::RectangleShape rect, optor::WidgetsState* state) 
    :   optor::Widget{std::move(rect), state},
        renderer_{rect_.GetSize()},
        scene_{rect_.GetSize()}
{
    ERROR_HANDLE(&optor::Scene::Update, scene_);
}

void optor::SceneWidget::Draw(hui::Window* window) {
    ERROR_HANDLE([this, window](){
        optor::Widget::Draw(window);
    });

    ERROR_HANDLE([this](){
        renderer_.Clear(optor::color::WindowBackground);
    });
    
    ERROR_HANDLE([this](){
        renderer_.Draw(scene_);
    });

    ERROR_HANDLE([this](){
        renderer_.Display();
    });

    hui::Sprite sprite = ERROR_HANDLE([this](){
        return hui::Sprite(ERROR_HANDLE(&hui::Renderer::GetTexture, renderer_));
    });

    ERROR_HANDLE(&hui::Sprite::SetPosition, &sprite, AbsCoord());

    ERROR_HANDLE(&hui::Window::Draw, window, sprite);
}

bool optor::SceneWidget::OnMouseMove(const hui::Event& event) {
    const hui::Vector2d mouseCoord = event.GetMouseCoord();
    const hui::Vector2d mouseOffset = (mouseCoord - state_->prevMouseCoord) * optor::CAMERA_ROTATE_SPEED;

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

bool optor::SceneWidget::OnKeyboardPress(const hui::Event& event) {
    if (state_->selectedWidget == this) {
        switch (event.GetKeyboardButton()) {
            case hui::Event::KeyboardButton::W: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::FORWARD);
                return true;
            }

            case hui::Event::KeyboardButton::S: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::BACKWARD);
                return true;
            }

            case hui::Event::KeyboardButton::A: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::LEFT);
                return true;
            }

            case hui::Event::KeyboardButton::D: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::RIGHT);
                return true;
            }

            case hui::Event::KeyboardButton::Space: {
                ERROR_HANDLE(&optor::Scene::SetMoveDir, scene_, optor::MoveDirection::UP);
                return true;
            }

            case hui::Event::KeyboardButton::LControl: {
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

bool optor::SceneWidget::OnKeyboardRelease(const hui::Event& event) {
    if (state_->selectedWidget == this) {
        if (event.GetKeyboardButton() == hui::Event::KeyboardButton::W
         || event.GetKeyboardButton() == hui::Event::KeyboardButton::S
         || event.GetKeyboardButton() == hui::Event::KeyboardButton::A
         || event.GetKeyboardButton() == hui::Event::KeyboardButton::D
         || event.GetKeyboardButton() == hui::Event::KeyboardButton::Space
         || event.GetKeyboardButton() == hui::Event::KeyboardButton::LControl
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

void optor::SceneWidget::RotateCamera(const hui::Vector2d& mouseOffset) {
    double speed = 0;
    optor::RotateDirection dir = optor::RotateDirection::RIGHT;

    if (mouseOffset.x > 0) {
        dir = optor::RotateDirection::RIGHT, 
        speed = mouseOffset.x;
    } else {
        dir = optor::RotateDirection::LEFT, 
        speed = -mouseOffset.x;
    }

    if (speed) {
        ERROR_HANDLE(&optor::Camera::Rotate, scene_.GetCamera(), dir, speed);
    }
    
    if (mouseOffset.y < 0) {
        dir = optor::RotateDirection::UP, 
        speed = -mouseOffset.y;
    } else {
        dir = optor::RotateDirection::DOWN, 
        speed = mouseOffset.y;
    }

    if (speed) {
        ERROR_HANDLE(&optor::Camera::Rotate, scene_.GetCamera(), dir, speed);
    }
}

void optor::SceneWidget::OnIdle() { 
    ERROR_HANDLE([this](){
        optor::Widget::OnIdle();
    });

    ERROR_HANDLE(&optor::Scene::Update, scene_); // TODO smart update

}

optor::OpticObj* optor::SceneWidget::AddObj(std::unique_ptr<optor::OpticObj> obj) {
    auto* objPtr = ERROR_HANDLE(&optor::Scene::AddObj, &scene_, std::move(obj));
    return objPtr;
}