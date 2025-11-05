#include <cassert>

#include "widgets/SceneWidget.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "optics/Camera.hpp"
#include "optics/Scene.hpp"
#include "widgets/Widget.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"

optor::SceneWidget::SceneWidget(dr4::Window* window, dr4::DR4Backend* backend, const dr4::Vec2f& size, 
                                optor::WidgetsState* state)
    :   optor::Widget{size, state},
        texture_{window->CreateTexture()},
        scene_{backend, size}
{
    ERROR_HANDLE([this, size](){
        texture_->SetSize(size);
    });

    ERROR_HANDLE(&optor::Scene::Update, scene_);
}

void optor::SceneWidget::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    // for (size_t i = 0; i < 100; ++i) {
    //     std::cerr << (int)scene_.GetImage()->GetArray()[i] << " ";
    // }
    // std::cerr << std::endl;

    if (state_->selectedObj) {
        auto rect = scene_.ProjectAABBToScreen(state_->selectedObj->GetAABB(), scene_.GetCamera(), rect_.rect.size);
        if (rect) {
            const auto& points = *rect;

            // Найдём минимальные и максимальные координаты x и y
            float minX = points[0].x, minY = points[0].y;
            float maxX = points[0].x, maxY = points[0].y;

            for (int i = 1; i < 4; ++i) {
                minX = std::min(minX, points[i].x);
                minY = std::min(minY, points[i].y);
                maxX = std::max(maxX, points[i].x);
                maxY = std::max(maxY, points[i].y);
            }

            dr4::Vec2f pos  = {minX, minY};
            dr4::Vec2f size = {maxX - minX, maxY - minY};

            dr4::Rectangle rect(
                dr4::Rect2f(pos, size),
                optor::color::Transparent,
                2,
                optor::color::Red
            );

            ERROR_HANDLE([this, &rect](){
                texture_->Draw(rect);
            });
        }
    }

    ERROR_HANDLE([this](){
        texture_->Draw(*scene_.GetImage(), {0, 0});
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
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
    
    ERROR_HANDLE([this](){
        optor::Widget::OnIdle();
    });

    ERROR_HANDLE(&optor::Scene::Update, scene_); // TODO smart update

}

optor::OpticObj* optor::SceneWidget::AddObj(std::unique_ptr<optor::OpticObj> obj) {
    auto* objPtr = ERROR_HANDLE(&optor::Scene::AddObj, &scene_, std::move(obj));
    return objPtr;
}

const optor::Camera& optor::SceneWidget::GetCamera() const  { return scene_.GetCamera(); }
      optor::Camera& optor::SceneWidget::GetCamera()        { return scene_.GetCamera(); }
const optor::Scene&  optor::SceneWidget::GetScene()  const  { return scene_; }