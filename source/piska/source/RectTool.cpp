#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>

#include "piska/RectTool.hpp"
#include "dr4/math/vec2.hpp"
#include "piska/Rect.hpp"

optor::pp::RectTool::RectTool(::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        rect_{nullptr},
        state_{cvs->GetState()},
        rectInd_(std::numeric_limits<size_t>::max()),
        startPos_{}
{}

std::string_view optor::pp::RectTool::Icon() const {
    return "RectToolIcon";
}

std::string_view optor::pp::RectTool::Name() const {
    return "RectTool";
}

bool optor::pp::RectTool::IsCurrentlyDrawing() const {
    return isDrawing_;
}


void optor::pp::RectTool::OnStart() {
    if (state_->selectedTool) {
        state_->selectedTool->OnEnd();
    }
    state_->selectedTool = this;
}

void optor::pp::RectTool::OnBreak() {
    if (isDrawing_) {
        assert(rect_);
        cvs_->DelShape(rectInd_);
    }
}

void optor::pp::RectTool::OnEnd() {
    if (isDrawing_) {
        isDrawing_ = false;
        rect_->OnSelect();
    }
}


bool optor::pp::RectTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (!isDrawing_) {
        isDrawing_ = true;

        rect_ = new optor::pp::Rect(cvs_->GetWindow(), cvs_->GetControlsTheme(), cvs_->GetState());
        rectInd_ = cvs_->AddShape(rect_);
        rect_->SetPos(evt.pos);
        startPos_ = evt.pos;
        return true;
    } else {
        isDrawing_ = false;
        rect_->OnSelect();
        return true;
    }

    return false;
}

bool optor::pp::RectTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    return false;
}

bool optor::pp::RectTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!isDrawing_) {
        return false;
    }

    assert(rect_);

    const float left = std::min(startPos_.x, evt.pos.x);
    const float right = std::max(startPos_.x, evt.pos.x);
    const float top = std::min(startPos_.y, evt.pos.y);
    const float bottom = std::max(startPos_.y, evt.pos.y);
    
    rect_->SetPos({left, top});
    rect_->SetSize({right - left, bottom - top});

    return true;
}
