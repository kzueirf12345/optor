#include "dr4/math/vec2.hpp"
#include "dr4/window.hpp"

#include "widgets/WidgetButtonCamera.hpp"
#include "global/Global.hpp"
#include "optics/Camera.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetButton.hpp"

optor::WidgetButtonCamera::WidgetButtonCamera(dr4::Window* window, const dr4::Vec2f& size, 
                                              optor::WidgetsState* state, 
                                              const std::string& text,
                                              optor::Camera* camera, MoveDirection dir)
    :   optor::WidgetButton(size, state),
        optor::Textable(text),
        texture_{window->CreateTexture()},
        camera_(camera),
        dir_(dir)
{
    ERROR_HANDLE([this, &size](){
        texture_->SetSize(size);
    });

    
    ERROR_HANDLE([this, &size](){
        const dr4::Vec2f localBounds = text_.GetBounds().size;
        text_.pos.x = (size.x - localBounds.x) / 2;
        text_.pos.y = (size.y - localBounds.y) / 2;
    });
}

void optor::WidgetButtonCamera::OnIdle() {
    if (isPressed_) {
        ERROR_HANDLE(&optor::Camera::Move, camera_, dir_, CAMERA_MOVE_SPEED);
    }

    ERROR_HANDLE([this](){
        optor::WidgetButton::OnIdle();
    });
}

void optor::WidgetButtonCamera::Draw(dr4::Texture &srcTexture) {
    const dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        texture_->Draw(rect_);
    });
    rect_.rect.pos = pos;

    ERROR_HANDLE([this](){
        texture_->Draw(text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
    });
}