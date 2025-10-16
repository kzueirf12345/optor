#include "widgets/SceneWidget.hpp"
#include "hui/Renderer.hpp"
#include "hui/Sprite.hpp"
#include "hui/Vector.hpp"
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
    const hui::Vector2d mouseOffset = mouseCoord - state_->prevMouseCoord;

    if (state_->selectedWidget == this) {
        if (mouseOffset.x > 0) {
            scene_.GetCamera().Rotate(optor::RotateDirection::RIGHT, mouseOffset.x * optor::CAMERA_ROTATE_SPEED);
        } else if (mouseOffset.x < 0) {
            scene_.GetCamera().Rotate(optor::RotateDirection::LEFT, -mouseOffset.x * optor::CAMERA_ROTATE_SPEED);
        }
        
        if (mouseOffset.y < 0) {
            scene_.GetCamera().Rotate(optor::RotateDirection::UP,   -mouseOffset.y * optor::CAMERA_ROTATE_SPEED);
        } else if (mouseOffset.y > 0) {
            scene_.GetCamera().Rotate(optor::RotateDirection::DOWN,  mouseOffset.y * optor::CAMERA_ROTATE_SPEED);
        }

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