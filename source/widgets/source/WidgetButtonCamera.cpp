#include "widgets/WidgetButtonCamera.hpp"
#include "global/Global.hpp"
#include "optics/Camera.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetButton.hpp"

optor::WidgetButtonCamera::WidgetButtonCamera(const hui::Vector2d& size, optor::WidgetsState* state, 
                                              const std::string& text,
                                              optor::Camera* camera, MoveDirection dir)
    :   optor::WidgetButtonText(size, state, text), camera_(camera), dir_{dir}
{}

void optor::WidgetButtonCamera::OnIdle() {
    if (isPressed_) {
        ERROR_HANDLE(&optor::Camera::Move, camera_, dir_, CAMERA_MOVE_SPEED);
    }

    ERROR_HANDLE([this](){
        optor::WidgetButton::OnIdle();
    });
}