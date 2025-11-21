#include <cassert>
#include <cmath>
#include <limits>

#include "piska/CircleTool.hpp"
#include "dr4/math/vec2.hpp"
#include "piska/Circle.hpp"

optor::pp::CircleTool::CircleTool(::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        circle_{nullptr},
        state_{cvs->GetState()},
        circleInd_(std::numeric_limits<size_t>::max()),
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
    if (state_->selectedTool) {
        state_->selectedTool->OnEnd();
    }
    state_->selectedTool = this;
}

void optor::pp::CircleTool::OnBreak() {
    if (isDrawing_) {
        assert(circle_);
        cvs_->DelShape(circleInd_);
    }
}

void optor::pp::CircleTool::OnEnd() {
    if (isDrawing_) {
        isDrawing_ = false;
        circle_->OnSelect();
    }
}

bool optor::pp::CircleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (!isDrawing_) {
        isDrawing_ = true;

        circle_ = new optor::pp::Circle(cvs_->GetWindow(), cvs_->GetControlsTheme(), cvs_->GetState());
        circleInd_ = cvs_->AddShape(circle_);
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
    const float dist2Center = std::sqrt(dist.x * dist.x + dist.y * dist.y);
    
    circle_->SetPos(startPos_ - dr4::Vec2f(dist2Center, dist2Center));
    circle_->SetRadius(dist2Center);

    return true;
}