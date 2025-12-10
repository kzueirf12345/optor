#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <memory>
#include <string_view>
#include <iostream>

#include "piska/TextTool.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "piska/Global.hpp"
#include "piska/Text.hpp"

optor::pp::TextTool::TextTool(const dr4::Font* font, ::pp::Canvas* cvs)
    :   cvs_{cvs},
        isDrawing_(false),
        text_{nullptr},
        keyHandled_(false),
        font_(font),
        tempText_(cvs_->GetWindow()->CreateText()),
        prevClickTime_(0),
        doubleClickDelay_(0.5)
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
        const std::string& str = text_->GetText()->GetText();
        const size_t n = str.size();
        size_t caretPos = FindLetterPos(evt.pos.x);

        const double nowTime = cvs_->GetWindow()->GetTime();

        if (nowTime - prevClickTime_ < doubleClickDelay_ && caretPos != 0 && !std::isspace(str[caretPos - 1])) {
            text_->SetIsSelectedSmth(true);

            ssize_t pos = caretPos - 1;
            for (;pos > -1 && !std::isspace(str[pos]); --pos);
            text_->SetSelectPos(pos + 1);

            pos = caretPos - 1;
            for (;pos < n && !std::isspace(str[pos]); ++pos);
            text_->SetCaretPos(pos);
        } 
        else {
            text_->SetCaretPos(caretPos);
            text_->SetSelectPos(caretPos);
            text_->SetInSelectMode(true);
        }


        prevClickTime_ = nowTime;
        return true;
    }

    return false;
}

bool optor::pp::TextTool::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (!isDrawing_) {
        return false;
    }

    if (text_->GetInSelectMode() && evt.button == CREATE_BUTTON) {

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

    if (HandleTextFinish(evt)) {
        return true;
    }

    if (HandleBackspace(evt)) {
        return true;
    }

    if (HandleDelete(evt)) {
        return true;
    }

    if (HandleArrowLeft(evt)) {
        return true;
    }

    if (HandleArrowRight(evt)) {
        return true;
    }

    if (HandleA(evt)) {
        return true;
    }

    if (HandleC(evt)) {
        return true;
    }

    if (HandleV(evt)) {
        return true;
    }

    if (HandleHome(evt)) {
        return true;
    }

    if (HandleEnd(evt)) {
        return true;
    }

    if (HandleX(evt)) {
        return true;
    }

    keyHandled_ = false;
    return false;
}

bool optor::pp::TextTool::HandleTextFinish(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_ENTER && evt.mods == dr4::KEYMOD_SHIFT) {
        isDrawing_ = false;
        text_->SetIsCreating(false);
        text_->OnSelect();
        return true;
    }

    return false;
}

bool optor::pp::TextTool::HandleBackspace(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_BACKSPACE) {
        if (text_->GetIsSelectedSmth()) {
            text_->EraseSelectedText();
        } 
        else {
            if (evt.mods & dr4::KEYMOD_CTRL) {
                const std::string& str = text_->GetText()->GetText();
                std::size_t pos = text_->GetCaretPos();

                while (pos > 0 && std::isspace(static_cast<unsigned char>(str[pos - 1]))) {
                    text_->EraseLeftText();
                    --pos;
                }

                while (pos > 0 && !std::isspace(static_cast<unsigned char>(str[pos - 1]))) {
                    text_->EraseLeftText();
                    --pos;
                }
            }
            else {
                text_->EraseLeftText();
            }
        }
        return true;
    }
    return false;
}

bool optor::pp::TextTool::HandleDelete(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_DELETE) {
        if (text_->GetIsSelectedSmth()) {
            text_->EraseSelectedText();
        } else {
            if (evt.mods & dr4::KEYMOD_CTRL) {
                const std::string str = text_->GetText()->GetText();
                std::size_t pos = text_->GetCaretPos();
                const std::size_t n = str.size();

                while (pos < n && !std::isspace(static_cast<unsigned char>(str[pos]))) {
                    text_->EraseRightText();
                    ++pos;
                }

                while (pos < n && std::isspace(static_cast<unsigned char>(str[pos]))) {
                    text_->EraseRightText();
                    ++pos;
                }

            }
            else {
                text_->EraseRightText();
            }
        }
        return true;
    }
    return false;
}

bool optor::pp::TextTool::HandleArrowLeft(const dr4::Event::KeyEvent& evt) {
    const size_t curCaretPos = text_->GetCaretPos();

   if (evt.sym == dr4::KEYCODE_LEFT) {
        if (curCaretPos == 0) {
            return true;
        }

        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!text_->GetIsSelectedSmth()) {
                text_->SetIsSelectedSmth(true);
                text_->SetSelectPos(curCaretPos);
            }
        } else {
            text_->SetIsSelectedSmth(false);
        }

        if (evt.mods & dr4::KEYMOD_CTRL) {
            const std::string& str = text_->GetText()->GetText();
            std::size_t pos = curCaretPos;

            while (pos > 0 && std::isspace(static_cast<unsigned char>(str[pos - 1]))) {
                --pos;
            }

            while (pos > 0 && !std::isspace(static_cast<unsigned char>(str[pos - 1]))) {
                --pos;
            }

            text_->SetCaretPos(pos);
        } else {
            text_->SetCaretPos(curCaretPos - 1);
        }

        return true;
    }
    return false;
}

bool optor::pp::TextTool::HandleArrowRight(const dr4::Event::KeyEvent& evt) {
    const size_t curCaretPos = text_->GetCaretPos();

    if (evt.sym == dr4::KEYCODE_RIGHT) {
        if (curCaretPos == text_->GetText()->GetText().size()) {
            return true;
        }

        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!text_->GetIsSelectedSmth()) {
                text_->SetIsSelectedSmth(true);
                text_->SetSelectPos(curCaretPos);
            }
        } else {
            text_->SetIsSelectedSmth(false);
        }

        if (evt.mods & dr4::KEYMOD_CTRL) {
            const std::string& str = text_->GetText()->GetText();
            std::size_t pos = curCaretPos;
            const std::size_t n = str.size();

            while (pos < n && !std::isspace(static_cast<unsigned char>(str[pos]))) {
                ++pos;
            }

            while (pos < n && std::isspace(static_cast<unsigned char>(str[pos]))) {
                ++pos;
            }

            text_->SetCaretPos(pos);
        } else {
            text_->SetCaretPos(curCaretPos + 1);
        }

        return true;
    }
    return false;
}

bool optor::pp::TextTool::HandleA(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_A && evt.mods & dr4::KEYMOD_CTRL)
    {
        if (!text_->GetIsSelectedSmth()) {
            text_->SetIsSelectedSmth(true);
        }
        const std::string& str = text_->GetText()->GetText();
        const std::size_t n = str.size();
        text_->SetSelectPos(0);
        text_->SetCaretPos(n);

        return true;
    }

    return false;
}

bool optor::pp::TextTool::HandleC(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_C && evt.mods & dr4::KEYMOD_CTRL) {
        if (text_->GetIsSelectedSmth() || text_->GetInSelectMode()) {
            const std::string str = text_->GetText()->GetText();
            const size_t selectPos = text_->GetSelectPos();
            const size_t caretPos = text_->GetCaretPos();

            const size_t min = std::min(selectPos, caretPos);
            const size_t max = std::max(selectPos, caretPos);

            cvs_->GetWindow()->SetClipboard(str.substr(min, max - min));
            return true;
        }
    }

    return false;
}
bool optor::pp::TextTool::HandleV(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_V && evt.mods & dr4::KEYMOD_CTRL) {
        if (text_->GetIsSelectedSmth() || text_->GetInSelectMode()) {
            text_->EraseSelectedText();
        }
        text_->InsertText(cvs_->GetWindow()->GetClipboard());
        return true;
    }

    return false;
}

bool optor::pp::TextTool::HandleX(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_X && evt.mods & dr4::KEYMOD_CTRL) {
        if (text_->GetIsSelectedSmth() || text_->GetInSelectMode()) {
            auto newEvt(evt);
            newEvt.sym = dr4::KEYCODE_C;
            HandleC(newEvt);
            text_->EraseSelectedText();
            return true;
        }
    }
    return false;
}

bool optor::pp::TextTool::HandleHome(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_HOME) {
        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!text_->GetIsSelectedSmth()) {
                text_->SetIsSelectedSmth(true);
            }
            text_->SetSelectPos(text_->GetCaretPos());
            text_->SetCaretPos(0);
        } else {
            text_->SetCaretPos(0);
            text_->SetIsSelectedSmth(false);
        }
        return true;
    }
    return false;
}

bool optor::pp::TextTool::HandleEnd(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_END) {
        const size_t textLen = text_->GetText()->GetText().size();
        
        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!text_->GetIsSelectedSmth()) {
                text_->SetIsSelectedSmth(true);
            }
            text_->SetSelectPos(text_->GetCaretPos());
            text_->SetCaretPos(textLen);
        } else {
            text_->SetCaretPos(textLen);
            text_->SetIsSelectedSmth(false);
        }
        return true;
    }
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