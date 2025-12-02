#include <cassert>
#include <cmath>

#include "piska/ArrowTool.hpp"
#include "dr4/math/vec2.hpp"
#include "piska/Arrow.hpp"
#include "piska/Global.hpp"

optor::pp::ArrowTool::ArrowTool(::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        arrow_{nullptr},
        startPos_{}
{}

std::string_view optor::pp::ArrowTool::Icon() const {
    return "ArrowToolIcon";
}

std::string_view optor::pp::ArrowTool::Name() const {
    return "ArrowTool";
}

bool optor::pp::ArrowTool::IsCurrentlyDrawing() const {
    return isDrawing_;
}

void optor::pp::ArrowTool::OnStart() {
}

void optor::pp::ArrowTool::OnBreak() {
    if (isDrawing_) {
        assert(arrow_);
        isDrawing_ = false;
        cvs_->DelShape(arrow_);
    }
}

void optor::pp::ArrowTool::OnEnd() {
    if (isDrawing_) {
        isDrawing_ = false;
        arrow_->OnSelect();
    }
}

bool optor::pp::ArrowTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (evt.button != CREATE_BUTTON) {
        return false;
    }

    if (!isDrawing_) {
        isDrawing_ = true;

        arrow_ = new optor::pp::Arrow(cvs_);
        cvs_->AddShape(arrow_);
        arrow_->SetPos(evt.pos);
        startPos_ = evt.pos;
        return true;
    } else {
        isDrawing_ = false;
        arrow_->OnSelect();
        return true;
    }

    return false;
}

bool optor::pp::ArrowTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    return false;
}

bool optor::pp::ArrowTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!isDrawing_) {
        return false;
    }

    assert(arrow_);

    arrow_->SetEnd(evt.pos);

    return true;
}