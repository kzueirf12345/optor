#include <cassert>
#include <cmath>

#include "piska/TextTool.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "piska/Text.hpp"

optor::pp::TextTool::TextTool(::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        text_{nullptr},
        keyHandled_(false)
{

}

std::string_view optor::pp::TextTool::Icon() const {
    return "TextToolIcon";
}

std::string_view optor::pp::TextTool::Name() const {
    return "TextTool";
}

bool optor::pp::TextTool::IsCurrentlyDrawing() const {
    return isDrawing_;
}


void optor::pp::TextTool::OnStart() {
}

void optor::pp::TextTool::OnBreak() {
    if (isDrawing_) {
        assert(text_);
        isDrawing_ = false;
        text_->SetIsCreating(false);
        cvs_->DelShape(text_);
    }
}

void optor::pp::TextTool::OnEnd() {
    if (isDrawing_) {
        isDrawing_ = false;
        text_->SetIsCreating(false);
        text_->OnSelect();
    }
}


bool optor::pp::TextTool::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (evt.button != CREATE_BUTTON) {
        return false;
    }

    if (!isDrawing_) {
        isDrawing_ = true;

        text_ = new optor::pp::Text(cvs_);
        cvs_->AddShape(text_);
        text_->SetPos(evt.pos);
        text_->SetIsCreating(true);
        text_->OnSelect();
        return true;
    } else {
        // TODO caretka
        return true;
    }

    return false;
}

bool optor::pp::TextTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    return false;
}

bool optor::pp::TextTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!isDrawing_) {
        return false;
    }

    // TODO select

    return false;
}


bool optor::pp::TextTool::OnKeyDown(const dr4::Event::KeyEvent &evt) {
    if (!isDrawing_) {
        return false;
    }

    keyHandled_ = true;

    if (evt.sym == dr4::KEYCODE_ENTER && evt.mods == dr4::KEYMOD_SHIFT) {
        isDrawing_ = false;
        text_->SetIsCreating(false);
        text_->OnSelect();
        return true;
    }

    if (evt.sym == dr4::KEYCODE_BACKSPACE) {
        text_->EraseLeftText();
        return true;
    }


    if (evt.sym == dr4::KEYCODE_DELETE) {
        text_->EraseRightText();
        return true;
    }

    const size_t curCaretPos = text_->GetCaretPos();

    if (evt.sym == dr4::KEYCODE_LEFT) {
        text_->SetCaretPos(curCaretPos ? curCaretPos - 1 : 0);
        return true;
    }

    if (evt.sym == dr4::KEYCODE_RIGHT) {
        text_->SetCaretPos(curCaretPos + 1);
        return true;
    }

    keyHandled_ = false;

    return false;
}
bool optor::pp::TextTool::OnText(const dr4::Event::TextEvent &evt) {
    if (!isDrawing_) {
        return false;
    }

    if (!keyHandled_) {
        text_->InsertText(evt.unicode);
        return true;
    } else {
        keyHandled_ = false;
    }
        

    return false;
}