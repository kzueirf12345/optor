#include <cmath>
#include <cassert>
#include <cstdio>
#include <iostream>

#include "piska/Text.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "piska/Global.hpp"

optor::pp::Text::Text(dr4::Window* dr4Window, const ::pp::ControlsTheme& theme, ::pp::Canvas* cvs) 
    :   text_{dr4Window->CreateText()},
        isDragged_(false),
        cvs_{cvs},
        selectRect_(dr4Window->CreateRectangle()),
        isResized_(false),
        activeSide_{optor::pp::Side::UNKNOWN},
        textStr_("Text:)"),
        isCreating_(false),
        caret_{cvs->GetWindow()->CreateLine()},
        caretBlinkPeriod_(0.2),
        caretPrevBlinkTime_(cvs->GetWindow()->GetTime()),
        caretIsHide_(false)
{
    text_->SetText(textStr_);
    text_->SetColor(theme.textColor);
    text_->SetFontSize(theme.baseFontSize);
    text_->SetFont(dr4Window->CreateFont());

    caret_->SetColor(theme.textColor);
    caret_->SetThickness(OutlineThickness);
    caret_->SetStart({0, 0});
    caret_->SetEnd({0, 0.7f * text_->GetBounds().y});

    selectRect_->SetBorderThickness(OutlineThickness);
    selectRect_->SetBorderColor(theme.lineColor);
    selectRect_->SetFillColor({0, 0, 0, 0});

    UpdateCaret();
    UpdateSelectRect();
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

    if (cvs_->GetSelectedShape() == this) {
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
}


::dr4::Vec2f optor::pp::Text::GetPos() const {
    return text_->GetPos();
}

void optor::pp::Text::PopBackText() {
    if (!textStr_.empty())
    {
        textStr_.pop_back();
        text_->SetText(textStr_);

        UpdateCaret();
        UpdateSelectRect();
    }
}

void optor::pp::Text::PushBackText(const std::string& addedText) {
    textStr_ += addedText;
    text_->SetText(textStr_);
    UpdateCaret();
    UpdateSelectRect();
}

void optor::pp::Text::SetIsCreating(bool isCreating) {
    isCreating_ = isCreating;
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
}


void optor::pp::Text::UpdateSelectRect()
{
    selectRect_->SetPos(text_->GetPos() - OutlineThicknessVec);
    selectRect_->SetSize(text_->GetBounds() + OutlineThicknessVec);
}

void optor::pp::Text::UpdateCaret() {
    std::cerr << text_->GetBounds().x << std::endl;
    caret_->SetPos(text_->GetPos() + dr4::Vec2f{text_->GetBounds().x + OutlineThickness, 0});
}