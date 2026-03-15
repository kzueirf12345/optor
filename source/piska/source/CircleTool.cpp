#include <cassert>
#include <cmath>

#include "piska/CircleTool.hpp"
#include "dr4/math/vec2.hpp"
#include "piska/Circle.hpp"
// #include "piska/ColorPicker.hpp"

optor::pp::CircleTool::CircleTool(::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        circle_{nullptr},
        startPos_{}
        // colorPicker_(nullptr)
{}

std::string_view optor::pp::CircleTool::Icon() const {
    return "\ueabc";
}

std::string_view optor::pp::CircleTool::Name() const {
    return "CircleTool";
}

bool optor::pp::CircleTool::IsCurrentlyDrawing() const {
    return isDrawing_;
}

void optor::pp::CircleTool::OnStart() {
    // colorPicker_ = new optor::pp::ColorPicker(cvs_);
    // cvs_->AddShape(colorPicker_);
    // cvs_->SetSelectedShape(colorPicker_);
}

void optor::pp::CircleTool::OnBreak() {
    // if (colorPicker_) {
    //     cvs_->DelShape(colorPicker_);
    //     colorPicker_ = nullptr;
    //     cvs_->SetSelectedShape(nullptr);
    // }
    if (isDrawing_) {
        assert(circle_);
        isDrawing_ = false;
        cvs_->DelShape(circle_);
    }
}

void optor::pp::CircleTool::OnEnd() {
    // if (colorPicker_) {
    //     cvs_->DelShape(colorPicker_);
    //     colorPicker_ = nullptr;
    //     cvs_->SetSelectedShape(nullptr);
    // }
    if (isDrawing_) {
        isDrawing_ = false;
        circle_->OnSelect();
    }
}

bool optor::pp::CircleTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    // if (colorPicker_) {
    //     if (colorPicker_->OnMouseDown(evt)) {
    //         return true;
    //     }
    // }

    if (evt.button != CREATE_BUTTON) {
        return false;
    }
    
    if (!isDrawing_) {
        isDrawing_ = true;

        circle_ = new optor::pp::Circle(cvs_);
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
    // if (colorPicker_) {
    //     if (colorPicker_->OnMouseUp(evt)) {
    //         return true;
    //     }
    // }
    return false;
}

bool optor::pp::CircleTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    // if (colorPicker_) {
    //     if (colorPicker_->OnMouseMove(evt)) {
    //         return true;
    //     }
    // }

    if (!isDrawing_) {
        return false;
    }

    assert(circle_);

    const dr4::Vec2f dist = evt.pos - startPos_;
    
    circle_->SetPos(startPos_ - dist);
    circle_->SetRadius(dist);

    return true;
}

// bool optor::pp::CircleTool::OnKeyDown(const dr4::Event::KeyEvent &evt) {
//     if (colorPicker_ && evt.sym == dr4::KEYCODE_ENTER) {
//         cvs_->GetControlsTheme().shapeBorderColor = colorPicker_->GetColor();
//         cvs_->DelShape(colorPicker_);
//         colorPicker_ = nullptr;
//         cvs_->SetSelectedShape(nullptr);

//         return true;
//     }

//     return false;
// }