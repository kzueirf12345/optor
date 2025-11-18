#include <cmath>

#include "geomprim/Arrow.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/mouse_buttons.hpp"
#include "geomprim/Backend.hpp"


optor::geomprim::Arrow::Arrow(dr4::Window* dr4Window)
    :   line_{dr4Window->CreateLine()},
        leftTip_(dr4Window->CreateLine()),
        rightTip_(dr4Window->CreateLine()),
        isDragged_(false),
        isResized_(false),
        activeSide_(optor::geomprim::Side::UNKNOWN),
        rect_{}
{
    line_->SetStart({0, 0});
    line_->SetEnd({100, 100});

    line_->SetColor(optor::geomprim::BorderColor);
    leftTip_->SetColor(optor::geomprim::BorderColor);
    rightTip_->SetColor(optor::geomprim::BorderColor);

    line_->SetThickness(10);
    leftTip_->SetThickness(10);
    rightTip_->SetThickness(10);

    rect_.size = {100, 100};

    UpdateTips();
}

bool optor::geomprim::Arrow::OnMouseMove(const dr4::Event& event) {
    if (isDragged_) {
        rect_.pos += event.mouseMove.rel;
        line_->SetPos(rect_.pos);
        leftTip_->SetPos(rect_.pos);
        rightTip_->SetPos(rect_.pos);
        return true;
    }

    if (isResized_) {
        Resize(event.mouseMove.rel);
        return true;
    }

    return false;
}

bool optor::geomprim::Arrow::OnMouseDown(const dr4::Event& event)    {

    if (event.mouseButton.button == dr4::MouseButtonType::LEFT) {
        if (OnOutline(event.mouseButton.pos)) {
            activeSide_ = ClosestSide(event.mouseButton.pos);
            isResized_ = true;
            return true;
        }

        if (OnMe(event.mouseButton.pos)) {
            isDragged_ = true;
            return true;
        }
    }

    return false;
}

bool optor::geomprim::Arrow::OnMouseRelease(const dr4::Event& event) {

    if (event.mouseButton.button == dr4::MouseButtonType::LEFT) {
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


void optor::geomprim::Arrow::DrawOn(dr4::Texture& texture) const {
    line_->DrawOn(texture);
    leftTip_->DrawOn(texture);
    rightTip_->DrawOn(texture);
}


void optor::geomprim::Arrow::SetPos(dr4::Vec2f pos) {
    line_->SetPos(rect_.pos);
    leftTip_->SetPos(rect_.pos);
    rightTip_->SetPos(rect_.pos);
    rect_.pos = pos;
}


dr4::Vec2f optor::geomprim::Arrow::GetPos() const {
    return rect_.pos;
}

bool optor::geomprim::Arrow::OnMe(dr4::Vec2f relCoord) const {

    return rect_.Contains(relCoord);
}

bool optor::geomprim::Arrow::OnOutline(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = rect_.pos;
    const dr4::Vec2f size = rect_.size;

    const dr4::Vec2f posOut = pos - OutlineThicknessVec;
    const dr4::Vec2f sizeOut = size + 2 * OutlineThicknessVec;

    const dr4::Vec2f posIn = pos + OutlineThicknessVec;
    const dr4::Vec2f sizeIn = size - 2 * OutlineThicknessVec;
    
    return dr4::Rect2f(posOut, sizeOut).Contains(relCoord) 
       && !dr4::Rect2f(posIn,  sizeIn) .Contains(relCoord);
}

optor::geomprim::Side optor::geomprim::Arrow::ClosestSide(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos  = rect_.pos;
    const dr4::Vec2f size = rect_.size;

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

void optor::geomprim::Arrow::Resize(dr4::Vec2f offset) {
    dr4::Vec2f pos  = rect_.pos;
    dr4::Vec2f size = rect_.size;

    switch (activeSide_) {

        case Side::LEFT: {
            float newWidth = size.x - offset.x;
            if (newWidth > 0.0f) {
                size.x = newWidth;
                pos.x += offset.x;
            }
            break;
        }

        case Side::RIGHT: {
            float newWidth = size.x + offset.x;
            if (newWidth > 0.0f) {
                size.x = newWidth;
            }
            break;
        }

        case Side::TOP: {
            float newHeight = size.y - offset.y;
            if (newHeight > 0.0f) {
                size.y = newHeight;
                pos.y += offset.y;
            }
            break;
        }

        case Side::BOTTOM: {
            float newHeight = size.y + offset.y;
            if (newHeight > 0.0f) {
                size.y = newHeight;
            }
            break;
        }

        case Side::UNKNOWN:
        default:
            return;
    }

    rect_.pos = pos;
    rect_.size = size;

    line_->SetEnd(size);
    UpdateTips();

    line_->SetPos(rect_.pos);
    leftTip_->SetPos(rect_.pos);
    rightTip_->SetPos(rect_.pos);
}

static dr4::Vec2f GetNormal(dr4::Vec2f vec) {
    return {vec.y, -vec.x};
}

void optor::geomprim::Arrow::UpdateTips() {
    const dr4::Vec2f vector = line_->GetEnd() - line_->GetStart();

    leftTip_->SetEnd(line_->GetEnd());
    rightTip_->SetEnd(line_->GetEnd());

    constexpr double TIP_SCALE = 0.1;

    const dr4::Vec2f ScaledTendril(-vector * TIP_SCALE);
    const dr4::Vec2f NormalTendril(GetNormal(ScaledTendril));
    const dr4::Vec2f    TanTendril(vector + 2.f * ScaledTendril);

    leftTip_->SetStart(TanTendril + NormalTendril);
    rightTip_->SetStart(TanTendril - NormalTendril);

    leftTip_->SetStart(line_->GetStart() + leftTip_->GetStart());
    rightTip_->SetStart(line_->GetStart() + rightTip_->GetStart());
}