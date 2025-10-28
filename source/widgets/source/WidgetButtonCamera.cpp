#include "widgets/WidgetButtonCamera.hpp"
#include "global/Global.hpp"
#include "optics/Camera.hpp"
#include "common/ErrorHandler.hpp"
#include "optics/Scene.hpp"
#include "widgets/WidgetButton.hpp"

optor::WidgetButtonCamera::WidgetButtonCamera(hui::RectangleShape rect, optor::WidgetsState* state, 
                                              optor::Camera* camera, MoveDirection dir)
    :   optor::WidgetButton(std::move(rect), state), camera_(camera), dir_{dir}
{}

void optor::WidgetButtonCamera::OnIdle() {
    if (isPressed_) {
        ERROR_HANDLE(&optor::Camera::Move, camera_, dir_, CAMERA_MOVE_SPEED);
    }

    ERROR_HANDLE([this](){
        optor::WidgetButton::OnIdle();
    });
}