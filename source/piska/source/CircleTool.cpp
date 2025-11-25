#include <cassert>
#include <cmath>

#include "piska/CircleTool.hpp"
#include "dr4/math/vec2.hpp"
#include "piska/Circle.hpp"

optor::pp::CircleTool::CircleTool(::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        circle_{nullptr},
        startPos_{}
{}

std::string_view optor::pp::CircleTool::Icon() const {
    return "CircleToolIcon";
}

std::string_view optor::pp::CircleTool::Name() const {
    return "CircleTool";
}

bool optor::pp::CircleTool::IsCurrentlyDrawing() const {
    return isDrawing_;
}

void optor::pp::CircleTool::OnStart() {
}

void optor::pp::CircleTool::OnBreak() {
    if (isDrawing_) {
        assert(circle_);
        isDrawing_ = false;
        cvs_->DelShape(circle_);
    }
}

void optor::pp::CircleTool::OnEnd() {
    if (isDrawing_) {
        isDrawing_ = false;
        circle_->OnSelect();
    }
}

bool optor::pp::CircleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (evt.button != CREATE_BUTTON) {
        return false;
    }
    
    if (!isDrawing_) {
        isDrawing_ = true;

        circle_ = new optor::pp::Circle(cvs_->GetWindow(), cvs_->GetControlsTheme(), cvs_);
        cvs_->AddShape(circle_);
        circle_->SetPos(evt.pos);
        startPos_ = evt.pos;
        return true;
    } else {
        isDrawing_ = false;
        circle_->OnSelect();
        return true;
    }

    return false;
}

bool optor::pp::CircleTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    return false;
}

bool optor::pp::CircleTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!isDrawing_) {
        return false;
    }

    assert(circle_);

    const dr4::Vec2f dist = evt.pos - startPos_;
    
    circle_->SetPos(startPos_ - dist);
    circle_->SetRadius(dist);

    return true;
}