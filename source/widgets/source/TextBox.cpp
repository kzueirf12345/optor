#include "widgets/TextBox.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/mouse_buttons.hpp"
#include "global/Global.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"

optor::TextBox::TextBox(const dr4::Vec2f& size, optor::WidgetsState* state, 
                        const std::string& text)
    :   Widget(size, state),
        Textable(text, state->window),
        texture_{state_->window->CreateTexture()},
        textStr_{text},
        keyHandled_{false},
        tempText_{state->window->CreateText()},
        prevClickTime_{0},
        doubleClickDelay_{0.5},
        caret_{state->window->CreateLine()},
        caretBlinkPeriod_{0.5},
        caretPrevBlinkTime_{state->window->GetTime()},
        caretPos_{textStr_.size()},
        inSelectMode_{false},
        selectPos_{0},
        isSelectedSmth_{false},
        selectedTextRect_{state->window->CreateRectangle()},
        caretIsHide_(false)
{
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_->GetSize());
    });

    SetIsDraggable(false);

    tempText_->SetFont(optor::FONT);

    caret_->SetColor(optor::color::TextPrimary);
    caret_->SetThickness(5);
    caret_->SetStart({0, 0.1f * size.y});
    caret_->SetEnd({0, 0.9f * size.y});

    selectedTextRect_->SetFillColor({optor::color::TextPrimary.r, optor::color::TextPrimary.g, optor::color::TextPrimary.b, 100});
    selectedTextRect_->SetSize({1, 1});

    UpdateCaret();
}

        
bool optor::TextBox::OnMousePress(const dr4::Event &evt) {
    if (isHide_) return false;

    const bool res = optor::Widget::OnMousePress(evt);

    if (this == state_->selectedWidget && evt.mouseButton.button == dr4::MouseButtonType::LEFT) {
        const size_t n = textStr_.size();
        size_t caretPos = FindLetterPos(evt.mouseButton.pos.x - AbsCoord().x);

        const double nowTime = state_->window->GetTime();

        if ((nowTime - prevClickTime_ < doubleClickDelay_)
         && (caretPos != 0) 
         && (!std::isspace(textStr_[caretPos - 1]))
         && (caretPos == caretPos_)
        ) {
            isSelectedSmth_ = true;

            ssize_t pos = caretPos - 1;
            for (; pos > -1 && !std::isspace(textStr_[pos]); --pos);

            SetSelectPos(pos + 1);

            pos = caretPos - 1;
            for (; pos < n && !std::isspace(textStr_[pos]); ++pos);

            SetCaretPos(pos);
        } 
        else {
            SetCaretPos(caretPos);
            SetSelectPos(caretPos);
            inSelectMode_ = true;
        }


        prevClickTime_ = nowTime;
        return true;
    }

    return res;
}

bool optor::TextBox::OnMouseRelease(const dr4::Event &evt) {
    if (isHide_) return false;

    if (inSelectMode_ && evt.mouseButton.button == dr4::MouseButtonType::LEFT) {

        inSelectMode_ = false;
        if (selectPos_ != caretPos_) {
            isSelectedSmth_ = true;
        }
        return true;
    }

    return optor::Widget::OnMouseRelease(evt);
}

bool optor::TextBox::OnMouseMove(const dr4::Event &evt) {
    if (isHide_) return false;

    if (inSelectMode_) {
        // std::cerr << "In selected mode OnMouseMove " << evt.mouseButton.pos.x - AbsCoord().x << "\n";
        size_t caretPos = FindLetterPos(evt.mouseMove.pos.x - AbsCoord().x);
        SetCaretPos(caretPos);

        return true;
    }

    return optor::Widget::OnMouseMove(evt);
}

bool optor::TextBox::OnKeyboardPress(const dr4::Event &evt) {
    if (isHide_) return false;

    if (state_->selectedWidget != this) {
        return false;
    }

    keyHandled_ = true;

    if (HandleTextFinish(evt.key)) {
        return true;
    }

    if (HandleBackspace(evt.key)) {
        return true;
    }

    if (HandleDelete(evt.key)) {
        return true;
    }

    if (HandleArrowLeft(evt.key)) {
        return true;
    }

    if (HandleArrowRight(evt.key)) {
        return true;
    }

    if (HandleA(evt.key)) {
        return true;
    }

    if (HandleC(evt.key)) {
        return true;
    }

    if (HandleV(evt.key)) {
        return true;
    }

    if (HandleHome(evt.key)) {
        return true;
    }

    if (HandleEnd(evt.key)) {
        return true;
    }

    if (HandleX(evt.key)) {
        return true;
    }

    keyHandled_ = false;

    return optor::Widget::OnKeyboardPress(evt);
}

bool optor::TextBox::OnTextInput(const dr4::Event &evt) {
    if (isHide_) return false;

    if (!keyHandled_) {
        if (isSelectedSmth_ || inSelectMode_) {
            EraseSelectedText();
        }
        InsertText(evt.text.unicode);
        return true;
    } 
    else {
        keyHandled_ = false;
    }

    return optor::Widget::OnTextInput(evt);
}

void optor::TextBox::Draw(dr4::Texture& srcTexture) {
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);
    
    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    if ((inSelectMode_ || isSelectedSmth_) && selectPos_ != caretPos_) {
        selectedTextRect_->DrawOn(*texture_);
    }

    if (state_->selectedWidget == this) {
        if (!caretIsHide_) {
            caret_->DrawOn(*texture_);
        }
        if (state_->window->GetTime() - caretPrevBlinkTime_ > caretBlinkPeriod_) {
            caretPrevBlinkTime_ = state_->window->GetTime();
            caretIsHide_ = !caretIsHide_;
        }
    }

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

void optor::TextBox::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

size_t optor::TextBox::FindLetterPos(float mousePosX) const {
    const float textPosX = text_->GetPos().x;
    size_t clickedPos = 0;

    tempText_->SetFontSize(text_->GetFontSize());
    const std::string& textStr(text_->GetText());

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


bool optor::TextBox::HandleTextFinish(const dr4::Event::KeyEvent& evt) {
    // if (evt.sym == dr4::KEYCODE_ENTER 
    //  && evt.mods == dr4::KEYMOD_SHIFT 
    //  && state_->selectedWidget == this
    // ) {
    //     state_->selectedWidget = nullptr;
    //     return true;
    // }

    return false;
}

bool optor::TextBox::HandleBackspace(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_BACKSPACE) {
        if (isSelectedSmth_) {
            EraseSelectedText();
        } 
        else {
            if (evt.mods & dr4::KEYMOD_CTRL) {
                std::size_t pos = caretPos_;

                while (pos > 0 && std::isspace(static_cast<unsigned char>(textStr_[pos - 1]))) {
                    EraseLeftText();
                    --pos;
                }

                while (pos > 0 && !std::isspace(static_cast<unsigned char>(textStr_[pos - 1]))) {
                    EraseLeftText();
                    --pos;
                }
            }
            else {
                EraseLeftText();
            }
        }
        return true;
    }
    return false;
}

bool optor::TextBox::HandleDelete(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_DELETE) {
        if (isSelectedSmth_) {
            EraseSelectedText();
        } else {
            if (evt.mods & dr4::KEYMOD_CTRL) {
                std::size_t pos = caretPos_;
                const std::size_t n = textStr_.size();

                while (pos < n && !std::isspace(static_cast<unsigned char>(textStr_[pos]))) {
                    EraseRightText();
                    ++pos;
                }

                while (pos < n && std::isspace(static_cast<unsigned char>(textStr_[pos]))) {
                    EraseRightText();
                    ++pos;
                }

            }
            else {
                EraseRightText();
            }
        }
        return true;
    }
    return false;
}

bool optor::TextBox::HandleArrowLeft(const dr4::Event::KeyEvent& evt) {
    const size_t curCaretPos = caretPos_;

   if (evt.sym == dr4::KEYCODE_LEFT) {
        if (curCaretPos == 0) {
            return true;
        }

        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!isSelectedSmth_) {
                isSelectedSmth_ = true;
                SetSelectPos(curCaretPos);
            }
        } else {
            isSelectedSmth_ = false;
        }

        if (evt.mods & dr4::KEYMOD_CTRL) {
            std::size_t pos = curCaretPos;

            while (pos > 0 && std::isspace(static_cast<unsigned char>(textStr_[pos - 1]))) {
                --pos;
            }

            while (pos > 0 && !std::isspace(static_cast<unsigned char>(textStr_[pos - 1]))) {
                --pos;
            }

            SetCaretPos(pos);
        } else {
            SetCaretPos(curCaretPos - 1);
        }

        return true;
    }

    return false;
}

bool optor::TextBox::HandleArrowRight(const dr4::Event::KeyEvent& evt) {
    const size_t curCaretPos = caretPos_;

    if (evt.sym == dr4::KEYCODE_RIGHT) {
        if (curCaretPos == textStr_.size()) {
            return true;
        }

        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!isSelectedSmth_) {
                isSelectedSmth_ = true;
                SetSelectPos(curCaretPos);
            }
        } else {
            isSelectedSmth_ = false;
        }

        if (evt.mods & dr4::KEYMOD_CTRL) {
            std::size_t pos = curCaretPos;
            const std::size_t n = textStr_.size();

            while (pos < n && !std::isspace(static_cast<unsigned char>(textStr_[pos]))) {
                ++pos;
            }

            while (pos < n && std::isspace(static_cast<unsigned char>(textStr_[pos]))) {
                ++pos;
            }

            SetCaretPos(pos);
        } else {
            SetCaretPos(curCaretPos + 1);
        }

        return true;
    }
    return false;
}

bool optor::TextBox::HandleA(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_A && evt.mods & dr4::KEYMOD_CTRL)
    {
        if (!isSelectedSmth_) {
            isSelectedSmth_ = true;
        }
        const std::size_t n = textStr_.size();
        SetSelectPos(0);
        SetCaretPos(n);

        return true;
    }

    return false;
}

bool optor::TextBox::HandleC(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_C && evt.mods & dr4::KEYMOD_CTRL) {
        if (isSelectedSmth_ || inSelectMode_) {
            const size_t selectPos = selectPos_;
            const size_t caretPos = caretPos_;

            const size_t min = std::min(selectPos, caretPos);
            const size_t max = std::max(selectPos, caretPos);

            state_->window->SetClipboard(textStr_.substr(min, max - min));
            return true;
        }
    }

    return false;
}

bool optor::TextBox::HandleV(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_V && evt.mods & dr4::KEYMOD_CTRL) {
        if (isSelectedSmth_ || inSelectMode_) {
            EraseSelectedText();
        }
        InsertText(state_->window->GetClipboard());
        return true;
    }

    return false;
}

bool optor::TextBox::HandleX(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_X && evt.mods & dr4::KEYMOD_CTRL) {
        if (isSelectedSmth_ || inSelectMode_) {
            auto newEvt(evt);
            newEvt.sym = dr4::KEYCODE_C;
            HandleC(newEvt);
            EraseSelectedText();
            return true;
        }
    }
    return false;
}

bool optor::TextBox::HandleHome(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_HOME) {
        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!isSelectedSmth_) {
                isSelectedSmth_ = true;
            }
            SetSelectPos(caretPos_);
            SetCaretPos(0);
        } else {
            SetCaretPos(0);
            isSelectedSmth_ = false;
        }
        return true;
    }
    return false;
}

bool optor::TextBox::HandleEnd(const dr4::Event::KeyEvent& evt) {
    if (evt.sym == dr4::KEYCODE_END) {
        const size_t textLen = textStr_.size();
        
        if (evt.mods & dr4::KEYMOD_SHIFT) {
            if (!isSelectedSmth_) {
                isSelectedSmth_ = true;
            }
            SetSelectPos(caretPos_);
            SetCaretPos(textLen);
        } else {
            SetCaretPos(textLen);
            isSelectedSmth_ = false;
        }
        return true;
    }
    return false;
}


void optor::TextBox::EraseLeftText() {
    if (caretPos_ == 0) {
        return;
    }

    textStr_.erase(caretPos_ - 1, 1);
    text_->SetText(textStr_);
    --caretPos_;

    UpdateCaret();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

void optor::TextBox::EraseRightText() {
    if (caretPos_ == textStr_.size()) {
        return;
    }

    textStr_.erase(caretPos_, 1);
    text_->SetText(textStr_);

    UpdateCaret();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

void optor::TextBox::EraseSelectedText() {
    if (caretPos_ == selectPos_) {
        return;
    }

    const size_t minPos = std::min(caretPos_, selectPos_);
    const size_t maxPos = std::max(caretPos_, selectPos_);
    textStr_.erase(minPos, maxPos - minPos);
    text_->SetText(textStr_);
    SetCaretPos(minPos);

    UpdateCaret();
    isSelectedSmth_ = false;
    inSelectMode_ = false;
}

void optor::TextBox::InsertText(const std::string& addedText) {
    textStr_.insert(caretPos_, addedText);
    
    text_->SetText(textStr_);
    caretPos_ += addedText.size();

    UpdateCaret();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}


void optor::TextBox::UpdateCaret() {
    tempText_->SetFontSize(text_->GetFontSize());
    tempText_->SetText(textStr_.substr(0, caretPos_));

    const float posX = text_->GetPos().x + tempText_->GetBounds().x + caret_->GetThickness();

    caret_->SetStart({posX, text_->GetPos().y + caret_->GetStart().y});
    caret_->SetEnd({posX, text_->GetPos().y + caret_->GetEnd().y});
}

void optor::TextBox::UpdateSelectedTextRect() {
    if (caretPos_ == selectPos_) {
        return;
    }

    tempText_->SetFontSize(text_->GetFontSize());

    tempText_->SetText(textStr_.substr(0, caretPos_));
    float firstOffset = tempText_->GetBounds().x;

    tempText_->SetText(textStr_.substr(0, selectPos_));
    float secondOffset = tempText_->GetBounds().x;

    if (firstOffset > secondOffset) {
        std::swap(firstOffset, secondOffset);
    }

    const dr4::Vec2f textPos = text_->GetPos();

    selectedTextRect_->SetPos(textPos + dr4::Vec2f(firstOffset, 0));
    selectedTextRect_->SetSize({
        secondOffset - firstOffset, 
        std::max(text_->GetBounds().y, caret_->GetEnd().y + 5) + 5
    });
}

void optor::TextBox::SetSelectPos(size_t selectPos) {
    selectPos_ = selectPos;
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

void optor::TextBox::SetCaretPos(size_t pos) {
    caretPos_ = std::min(pos, textStr_.size());
    UpdateCaret();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

