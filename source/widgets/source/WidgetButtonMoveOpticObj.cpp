#include "dr4/math/vec2.hpp"
#include "dr4/window.hpp"

#include "optics/OpticObj.hpp"
#include "optics/Vector.hpp"
#include "widgets/WidgetButtonMoveOpticObj.hpp"
#include "optics/Camera.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/Textable.hpp"
#include "widgets/WidgetButton.hpp"

optor::WidgetButtonMoveOpticObj::WidgetButtonMoveOpticObj(dr4::Window* window, const dr4::Vec2f& size, 
                                              optor::WidgetsState* state, 
                                              const std::string& text,
                                              optor::OpticObj* obj, MoveDirection dir)
    :   optor::WidgetButton(size, state),
        optor::Textable(text),
        texture_{window->CreateTexture()},
        obj_(obj),
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

void optor::WidgetButtonMoveOpticObj::OnIdle() {
    optor::Vector3d offset = {};

    switch (dir_) {
        case optor::MoveDirection::FORWARD:    { offset = { 0,  0,  1}; break; }
        case optor::MoveDirection::BACKWARD:   { offset = { 0,  0, -1}; break; }
        case optor::MoveDirection::UP:         { offset = { 0,  1,  0}; break; }
        case optor::MoveDirection::DOWN:       { offset = { 0, -1,  0}; break; }
        case optor::MoveDirection::RIGHT:      { offset = { 1,  0,  0}; break; }
        case optor::MoveDirection::LEFT:       { offset = {-1,  0,  0}; break; }
        case optor::MoveDirection::UNKNOWN:
        default:
            throw std::overflow_error("Unknown move direction enum");
    }

    if (isPressed_) {
        ERROR_HANDLE(&optor::OpticObj::Move, state_->selectedObj, offset);
    }

    ERROR_HANDLE([this](){
        optor::WidgetButton::OnIdle();
    });
}

void optor::WidgetButtonMoveOpticObj::Draw(dr4::Texture &srcTexture) {
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    ERROR_HANDLE([this](){
        texture_->Draw(text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
    });
}