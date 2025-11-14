#include <cmath>

#include "geomprim/Circle.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/mouse_buttons.hpp"
#include "geomprim/Backend.hpp"


optor::geomprim::Circle::Circle(dr4::Window* dr4Window)
    :   circle_{dr4Window->CreateCircle()},
        isDragged_(false),
        isResized_(false),
        activeSide_(optor::geomprim::Side::UNKNOWN),
        rect_{}
{
    circle_->SetRadius(50.0f);
    circle_->SetBorderThickness(-10.0f);
    circle_->SetBorderColor(optor::geomprim::BorderColor);
    circle_->SetFillColor(optor::geomprim::TransparentColor);

    rect_.size = {2.f * 50.f, 2.f * 50.f};
}

bool optor::geomprim::Circle::OnMouseMove(const dr4::Event& event) {
    if (isDragged_) {
        rect_.pos += event.mouseMove.rel;
        circle_->SetPos(rect_.pos);
        return true;
    }

    if (isResized_) {
        Resize(event.mouseMove.rel);
        return true;
    }

    return false;
}

bool optor::geomprim::Circle::OnMouseDown(const dr4::Event& event)    {

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

bool optor::geomprim::Circle::OnMouseRelease(const dr4::Event& event) {

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


void optor::geomprim::Circle::DrawOn(dr4::Texture& texture) const {
    circle_->DrawOn(texture);
}


void optor::geomprim::Circle::SetPos(dr4::Vec2f pos) {
    circle_->SetPos(pos);
    rect_.pos = pos;
}


dr4::Vec2f optor::geomprim::Circle::GetPos() const {
    return rect_.pos;
}

bool optor::geomprim::Circle::OnMe(dr4::Vec2f relCoord) const {

    return rect_.Contains(relCoord);
}
bool optor::geomprim::Circle::OnBorder(dr4::Vec2f relCoord) const {
    const dr4::Vec2f thicknessVec = {circle_->GetBorderThickness(), circle_->GetBorderThickness()};
    const dr4::Vec2f posIn = rect_.pos + thicknessVec;
    const dr4::Vec2f sizeIn = rect_.size - 2 * thicknessVec;

    return OnMe(relCoord) && !dr4::Rect2f(posIn, sizeIn).Contains(relCoord);
}

bool optor::geomprim::Circle::OnOutline(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = rect_.pos;
    const dr4::Vec2f size = rect_.size;

    const dr4::Vec2f posOut = pos - OutlineThicknessVec;
    const dr4::Vec2f sizeOut = size + 2 * OutlineThicknessVec;

    const dr4::Vec2f posIn = pos + OutlineThicknessVec;
    const dr4::Vec2f sizeIn = size - 2 * OutlineThicknessVec;
    
    return dr4::Rect2f(posOut, sizeOut).Contains(relCoord) 
       && !dr4::Rect2f(posIn,  sizeIn) .Contains(relCoord);
}

optor::geomprim::Side optor::geomprim::Circle::ClosestSide(dr4::Vec2f relCoord) const {
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

void optor::geomprim::Circle::Resize(dr4::Vec2f offset) {
    dr4::Vec2f pos  = rect_.pos;
    float sideSize = rect_.size.x;

    switch (activeSide_) {

        case Side::LEFT: {
            float newWidth = sideSize - offset.x;
            if (newWidth > 0.0f) {
                sideSize = newWidth;
                pos += offset;
            }
            break;
        }

        case Side::RIGHT: {
            float newWidth = sideSize + offset.x;
            if (newWidth > 0.0f) {
                sideSize = newWidth;
            }
            break;
        }

        case Side::TOP: {
            float newHeight = sideSize - offset.y;
            if (newHeight > 0.0f) {
                sideSize = newHeight;
                pos += offset;
            }
            break;
        }

        case Side::BOTTOM: {
            float newHeight = sideSize + offset.y;
            if (newHeight > 0.0f) {
                sideSize = newHeight;
            }
            break;
        }

        case Side::UNKNOWN:
        default:
            return;
    }

    rect_.pos = pos;
    rect_.size = {sideSize, sideSize};

    circle_->SetRadius(sideSize / 2.f);
    circle_->SetPos(pos);
}
