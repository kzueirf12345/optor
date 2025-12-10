#include <cmath>
#include <cassert>
#include <cstdio>
#include <memory>

#include "piska/Text.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "piska/Global.hpp"

optor::pp::Text::Text(const dr4::Font* font, ::pp::Canvas* cvs) 
    :   text_{cvs->GetWindow()->CreateText()},
        tempText_(cvs->GetWindow()->CreateText()),
        isDragged_(false),
        cvs_{cvs},
        selectRect_(cvs->GetWindow()->CreateRectangle()),
        isResized_(false),
        activeSide_{optor::pp::Side::UNKNOWN},
        textStr_("Text:)"),
        isCreating_(false),
        caret_{cvs->GetWindow()->CreateLine()},
        caretBlinkPeriod_(0.5),
        caretPrevBlinkTime_(cvs->GetWindow()->GetTime()),
        caretIsHide_(false),
        caretPos_(textStr_.size()),
        inSelectMode_(false),
        isSelectedSmth_(false),
        selectPos_(0),
        selectedTextRect_(cvs->GetWindow()->CreateRectangle())
{
    text_->SetText(textStr_);
    text_->SetColor(cvs->GetControlsTheme().textColor);
    text_->SetFontSize(cvs->GetControlsTheme().baseFontSize);
    text_->SetFont(font);

    tempText_->SetFont(font);

    caret_->SetColor(cvs->GetControlsTheme().textColor);
    caret_->SetThickness(OutlineThickness);
    caret_->SetStart({0, 0});
    caret_->SetEnd({0, 0.7f * text_->GetBounds().y});

    const dr4::Color selectColor = cvs->GetControlsTheme().selectColor;
    selectedTextRect_->SetFillColor({selectColor.r, selectColor.g, selectColor.b, 100});
    selectedTextRect_->SetSize({1, 1});

    selectRect_->SetBorderThickness(OutlineThickness);
    selectRect_->SetBorderColor(cvs->GetControlsTheme().selectColor);
    selectRect_->SetFillColor({0, 0, 0, 0});

    UpdateCaret();
}

bool optor::pp::Text::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (evt.button == dr4::MouseButtonType::LEFT) {
        OnSelect();

        if (OnOutline(evt.pos)) {
            activeSide_ = ClosestSide(evt.pos);
            isResized_ = true;
            return true;
        }

        if (OnMe(evt.pos)) {
            isDragged_ = true;
            return true;
        }
    }

    return false;
}

bool optor::pp::Text::OnMouseUp(const dr4::Event::MouseButton &evt) {

    if (evt.button == dr4::MouseButtonType::LEFT) {
        if (isResized_) {
            isResized_ = false;
            return true;
        }

        if (isDragged_) {
            isDragged_ = false;
            return true;
        }
    }

    return false;

}

bool optor::pp::Text::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (isDragged_) {
        SetPos(text_->GetPos() + evt.rel);
        return true;
    }

    if (isResized_) {
        ResizeBySide(evt.rel);
        return true;
    }

    return false;
}


void optor::pp::Text::OnSelect() {
    if (cvs_->GetSelectedShape() != nullptr) {
        cvs_->GetSelectedShape()->OnDeselect();
    }
    cvs_->SetSelectedShape(this);
}

void optor::pp::Text::OnDeselect() {
}


void optor::pp::Text::DrawOn(::dr4::Texture& texture) const {

    text_->DrawOn(texture);

    if ((inSelectMode_ || isSelectedSmth_) && selectPos_ != caretPos_) {
        selectedTextRect_->DrawOn(texture);
    }

    if (cvs_->GetSelectedShape() == this || isCreating_) {
        selectRect_->DrawOn(texture);
    }

    if (isCreating_) {
        if (!caretIsHide_) {
            caret_->DrawOn(texture);
        }
        if (cvs_->GetWindow()->GetTime() - caretPrevBlinkTime_ > caretBlinkPeriod_) {
            caretPrevBlinkTime_ = cvs_->GetWindow()->GetTime();
            caretIsHide_ = !caretIsHide_;
        }
    }
}


void optor::pp::Text::SetPos(::dr4::Vec2f pos) {
    text_->SetPos(pos);
    UpdateCaret();
    UpdateSelectRect();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}


::dr4::Vec2f optor::pp::Text::GetPos() const {
    return text_->GetPos();
}

void optor::pp::Text::EraseLeftText() {
    if (caretPos_ == 0) {
        return;
    }

    textStr_.erase(caretPos_ - 1, 1);
    text_->SetText(textStr_);
    --caretPos_;

    UpdateCaret();
    UpdateSelectRect();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

void optor::pp::Text::EraseRightText() {
    if (caretPos_ == textStr_.size()) {
        return;
    }

    textStr_.erase(caretPos_, 1);
    text_->SetText(textStr_);

    UpdateCaret();
    UpdateSelectRect();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

void optor::pp::Text::EraseSelectedText() {
    if (caretPos_ == selectPos_) {
        return;
    }

    const size_t minPos = std::min(caretPos_, selectPos_);
    const size_t maxPos = std::max(caretPos_, selectPos_);
    textStr_.erase(minPos, maxPos - minPos);
    text_->SetText(textStr_);
    SetCaretPos(minPos);

    UpdateCaret();
    UpdateSelectRect();
    SetIsSelectedSmth(false);
    SetInSelectMode(false);
}

void optor::pp::Text::InsertText(const std::string& addedText) {

    textStr_.insert(caretPos_, addedText);
    
    text_->SetText(textStr_);
    caretPos_ += addedText.size();

    UpdateCaret();
    UpdateSelectRect();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

size_t optor::pp::Text::GetCaretPos() const {
    return caretPos_;
}

void optor::pp::Text::SetCaretPos(size_t pos) {
    caretPos_ = std::min(pos, textStr_.size());
    UpdateCaret();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

void optor::pp::Text::SetIsCreating(bool isCreating) {
    isCreating_ = isCreating;
    if (!isCreating_) {
        isSelectedSmth_ = false;
        inSelectMode_ = false;
    }
}

void optor::pp::Text::SetInSelectMode(bool inSelectMode) {
    inSelectMode_ = inSelectMode;
}
void optor::pp::Text::SetIsSelectedSmth(bool isSelectedSmth) {
    isSelectedSmth_ = isSelectedSmth;
}
void optor::pp::Text::SetSelectPos(size_t selectPos) {
    selectPos_ = selectPos;
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}

bool optor::pp::Text::GetInSelectMode() {
    return inSelectMode_;
}
bool optor::pp::Text::GetIsSelectedSmth() {
    return isSelectedSmth_;
}
size_t optor::pp::Text::GetSelectPos() {
    return selectPos_;
}

const dr4::Text* optor::pp::Text::GetText() const {
    return text_.get();
}


bool optor::pp::Text::OnMe(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = text_->GetPos();

    const dr4::Vec2f size = text_->GetBounds();

    return dr4::Rect2f(pos, size).Contains(relCoord);
}

bool optor::pp::Text::OnOutline(dr4::Vec2f relCoord) const {
    const dr4::Vec2f posIn = selectRect_->GetPos();
    const dr4::Vec2f sizeIn = selectRect_->GetSize();

    const dr4::Vec2f posOut = posIn - dr4::Vec2f(selectRect_->GetBorderThickness(), selectRect_->GetBorderThickness());
    const dr4::Vec2f sizeOut = sizeIn + 2 * dr4::Vec2f(selectRect_->GetBorderThickness(), selectRect_->GetBorderThickness());
    
    return dr4::Rect2f(posOut, sizeOut).Contains(relCoord) 
       && !dr4::Rect2f(posIn,  sizeIn) .Contains(relCoord);
}

optor::pp::Side optor::pp::Text::ClosestSide(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos  = text_->GetPos();
    const dr4::Vec2f size = text_->GetBounds();

    const float left   = pos.x;
    const float right  = pos.x + size.x;
    const float top    = pos.y;
    const float bottom = pos.y + size.y;

    const float x = relCoord.x;
    const float y = relCoord.y;

    float distTop    = std::fabs(y - top);
    float distBottom = std::fabs(y - bottom);
    float distLeft   = std::fabs(x - left);
    float distRight  = std::fabs(x - right);

    float minDist = distTop;
    Side minSide = Side::TOP;

    if (distBottom < minDist) {
        minDist = distBottom;
        minSide = Side::BOTTOM;
    }
    if (distLeft < minDist) {
        minDist = distLeft;
        minSide = Side::LEFT;
    }
    if (distRight < minDist) {
        minDist = distRight;
        minSide = Side::RIGHT;
    }

    return minSide;
}

void optor::pp::Text::ResizeBySide(dr4::Vec2f offset) {
    dr4::Vec2f pos  = text_->GetPos();
    dr4::Vec2f prevSize = text_->GetBounds();

    float scale = 1;
    bool needChangePos = false;

    switch (activeSide_) {

        case Side::LEFT: {
            float newWidth = prevSize.x - offset.x;
            if (newWidth > 0.0f) {
                scale = newWidth / prevSize.x;
                needChangePos = true;
            }
            break;
        }

        case Side::RIGHT: {
            float newWidth = prevSize.x + offset.x;
            if (newWidth > 0.0f) {
                scale = newWidth / prevSize.x;
            }
            break;
        }

        case Side::TOP: {
            float newHeight = prevSize.y - offset.y;
            if (newHeight > 0.0f) {
                scale = newHeight / prevSize.y;
                needChangePos = true;
            }
            break;
        }

        case Side::BOTTOM: {
            float newHeight = prevSize.y + offset.y;
            if (newHeight > 0.0f) {
                scale = newHeight / prevSize.y;
            }
            break;
        }

        case Side::UNKNOWN:
        default:
            return;
    }

    text_->SetFontSize(scale * text_->GetFontSize());

    if (needChangePos) {
        dr4::Vec2f newSize = text_->GetBounds();
        text_->SetPos(pos - newSize + prevSize);
    }
    
    UpdateCaret();
    UpdateSelectRect();
    if (isSelectedSmth_ || inSelectMode_) {
        UpdateSelectedTextRect();
    }
}


void optor::pp::Text::UpdateSelectRect()
{
    selectRect_->SetPos(text_->GetPos() - OutlineThicknessVec);
    selectRect_->SetSize({
        text_->GetBounds().x + OutlineThickness + caret_->GetThickness(),
        std::max(text_->GetBounds().y, caret_->GetEnd().y + OutlineThickness) + OutlineThickness
    });
}

void optor::pp::Text::UpdateCaret() {
    tempText_->SetFontSize(text_->GetFontSize());
    tempText_->SetText(textStr_.substr(0, caretPos_));
    caret_->SetPos(text_->GetPos() + dr4::Vec2f{tempText_->GetBounds().x + OutlineThickness, 0});
}

void optor::pp::Text::UpdateSelectedTextRect() {
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
        std::max(text_->GetBounds().y, caret_->GetEnd().y + OutlineThickness) + OutlineThickness
    });
}