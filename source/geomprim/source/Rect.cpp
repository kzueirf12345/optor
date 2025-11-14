#include <cmath>
#include <iostream>

#include "geomprim/Rect.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/mouse_buttons.hpp"
#include "geomprim/Backend.hpp"

optor::geomprim::Rect::Rect(dr4::Window* dr4Window)
    :   rect_{dr4Window->CreateRectangle()},
        isResized_(false),
        isDragged_(false),
        activeSide_(optor::geomprim::Side::UNKNOWN)
{
    rect_->SetSize({100, 100});
    rect_->SetBorderThickness(-10);
    rect_->SetBorderColor(optor::geomprim::BorderColor);
    rect_->SetFillColor(optor::geomprim::TransparentColor);
}

bool optor::geomprim::Rect::OnMouseMove(const dr4::Event& event)    {
    if (isDragged_) {
        rect_->SetPos(rect_->GetPos() + event.mouseMove.rel);
        return true;
    }

    if (isResized_) {
        Resize(event.mouseMove.rel);
        return true;
    }
    
    return false;
}

bool optor::geomprim::Rect::OnMouseDown(const dr4::Event& event)    {

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

bool optor::geomprim::Rect::OnMouseRelease(const dr4::Event& event) {

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


void optor::geomprim::Rect::DrawOn(dr4::Texture& texture) const {
    rect_->DrawOn(texture);
}


void optor::geomprim::Rect::SetPos(dr4::Vec2f pos) {
    rect_->SetPos(pos);
}


dr4::Vec2f optor::geomprim::Rect::GetPos() const {
    return rect_->GetPos();
}

bool optor::geomprim::Rect::OnMe(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = rect_->GetPos();

    const dr4::Vec2f size = rect_->GetSize();

    return dr4::Rect2f(pos, size).Contains(relCoord);
}
bool optor::geomprim::Rect::OnBorder(dr4::Vec2f relCoord) const {
    const dr4::Vec2f thicknessVec = {rect_->GetBorderThickness(), rect_->GetBorderThickness()};
    const dr4::Vec2f posIn = rect_->GetPos() + thicknessVec;
    const dr4::Vec2f sizeIn = rect_->GetSize() - 2 * thicknessVec;

    return OnMe(relCoord) && !dr4::Rect2f(posIn, sizeIn).Contains(relCoord);
}
bool optor::geomprim::Rect::OnOutline(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = rect_->GetPos();
    const dr4::Vec2f size = rect_->GetSize();

    const dr4::Vec2f posOut = pos - OutlineThicknessVec;
    const dr4::Vec2f sizeOut = size + 2 * OutlineThicknessVec;

    const dr4::Vec2f posIn = pos + OutlineThicknessVec;
    const dr4::Vec2f sizeIn = size - 2 * OutlineThicknessVec;
    
    return dr4::Rect2f(posOut, sizeOut).Contains(relCoord) 
       && !dr4::Rect2f(posIn,  sizeIn) .Contains(relCoord);
}

optor::geomprim::Side optor::geomprim::Rect::ClosestSide(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos  = rect_->GetPos();
    const dr4::Vec2f size = rect_->GetSize();

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

void optor::geomprim::Rect::Resize(dr4::Vec2f offset) {
    dr4::Vec2f pos  = rect_->GetPos();
    dr4::Vec2f size = rect_->GetSize();

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

    rect_->SetPos(pos);
    rect_->SetSize(size);
}
