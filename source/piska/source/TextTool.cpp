#include <cassert>
#include <cmath>
#include <memory>
#include <string_view>
#include <iostream>

#include "piska/TextTool.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "piska/Global.hpp"
#include "piska/Text.hpp"

optor::pp::TextTool::TextTool(dr4::Font* font, ::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        text_{nullptr},
        keyHandled_(false),
        font_(font),
        tempText_(cvs_->GetWindow()->CreateText())
{
    tempText_->SetFont(font);
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
    if (!isDrawing_ && evt.button == CREATE_BUTTON) {
        isDrawing_ = true;

        text_ = new optor::pp::Text(font_, cvs_);
        cvs_->AddShape(text_);
        text_->SetPos(evt.pos);
        text_->SetIsCreating(true);
        text_->OnSelect();
        return true;
    }

    if (isDrawing_) {
        text_->SetIsSelectedSmth(false);
    }

    if (isDrawing_ && evt.button == CREATE_BUTTON && text_->OnMe(evt.pos)) {
        std::cerr << "start\n";
        size_t caretPos = FindLetterPos(evt.pos.x);

        // std::cerr << "caret pos in create " << caretPos << std::endl;
        text_->SetCaretPos(caretPos);
        text_->SetSelectPos(caretPos);
        text_->SetInSelectMode(true);
        return true;
    }

    return false;
}

bool optor::pp::TextTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!isDrawing_) {
        return false;
    }

    if (text_->GetInSelectMode() && evt.button == CREATE_BUTTON) {

        std::cerr << "end\n";
        text_->SetInSelectMode(false);
        if (text_->GetSelectPos() != text_->GetCaretPos()) {
            text_->SetIsSelectedSmth(true);
        }
    }

    return false;
}

bool optor::pp::TextTool::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (!isDrawing_) {
        return false;
    }

    if (text_->GetInSelectMode()) {
        size_t caretPos = FindLetterPos(evt.pos.x);
        text_->SetCaretPos(caretPos);
    }

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
        if (text_->GetIsSelectedSmth()) {
            text_->EraseSelectedText();
        } else {
            text_->EraseLeftText();
        }
        return true;
    }


    if (evt.sym == dr4::KEYCODE_DELETE) {
        if (text_->GetIsSelectedSmth()) {
            text_->EraseSelectedText();
        } else {
            text_->EraseRightText();
        }
        return true;
    }

    const size_t curCaretPos = text_->GetCaretPos();

    if (evt.sym == dr4::KEYCODE_LEFT) {
        if (curCaretPos == 0) {
            return true;
        }

        if(evt.mods == dr4::KEYMOD_SHIFT) {
            if (!text_->GetIsSelectedSmth()) {
                text_->SetIsSelectedSmth(true);
                text_->SetSelectPos(curCaretPos);
            }
        } else {
            text_->SetIsSelectedSmth(false);
        }
        text_->SetCaretPos(curCaretPos ? curCaretPos - 1 : 0);
        return true;
    }

    if (evt.sym == dr4::KEYCODE_RIGHT) {
        if (curCaretPos == text_->GetText()->GetText().size()) {
            return true;
        }

        if(evt.mods == dr4::KEYMOD_SHIFT) {
            if (!text_->GetIsSelectedSmth()) {
                text_->SetIsSelectedSmth(true);
                text_->SetSelectPos(curCaretPos);
            }
        } else {
            text_->SetIsSelectedSmth(false);
        }
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
        if (text_->GetIsSelectedSmth() || text_->GetInSelectMode()) {
            text_->EraseSelectedText();
        }
        text_->InsertText(evt.unicode);
        return true;
    } else {
        keyHandled_ = false;
    }
        

    return false;
}

size_t optor::pp::TextTool::FindLetterPos(float mousePosX) const {
    const float textPosX = text_->GetPos().x;
    size_t clickedPos = 0;

    tempText_->SetFontSize(text_->GetText()->GetFontSize());
    const std::string& textStr(text_->GetText()->GetText());

    for(; clickedPos < textStr.size(); ++clickedPos) {
        tempText_->SetText(std::string(textStr.begin(), textStr.begin() + clickedPos));

        const float mainBoundsX = tempText_->GetBounds().x;

        float letterOffset = 0;

        // if (clickedPos != 0) { // TODO
        //     char sym = textStr[clickedPos - 1];
        //     const std::string symStr = {sym};
        //     tempText_->SetText(symStr);
        //     letterOffset = tempText_->GetBounds().x;
        // }

        if (mousePosX <= textPosX + tempText_->GetBounds().x - letterOffset) {
            break;
        }
    }
    return clickedPos;
}