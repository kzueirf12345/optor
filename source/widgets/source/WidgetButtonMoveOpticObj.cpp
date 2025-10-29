#include <cassert>

#include "hui/Vector.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/WidgetButtonMoveOpticObj.hpp"
#include "optics/Camera.hpp"
#include "common/ErrorHandler.hpp"
#include "widgets/WidgetButton.hpp"
#include <stdexcept>

optor::WidgetButtonMoveOpticObj::WidgetButtonMoveOpticObj(const hui::Vector2d& size, 
                                                          optor::WidgetsState* state, 
                                                          const std::string& text,
                                                          optor::OpticObj* obj, MoveDirection dir)
    :   optor::WidgetButtonText(size, state, text), obj_(obj), dir_{dir}
{}

void optor::WidgetButtonMoveOpticObj::OnIdle() {
    hui::Vector3d offset = {};

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

    if (isPressed_ && state_->selectedObj) {
        ERROR_HANDLE(&optor::OpticObj::Move, state_->selectedObj, offset);
    }

    ERROR_HANDLE([this](){
        optor::WidgetButton::OnIdle();
    });
}

void optor::WidgetButtonMoveOpticObj::SetObj(optor::OpticObj* obj) {
    assert(obj);

    obj_ = obj;
}