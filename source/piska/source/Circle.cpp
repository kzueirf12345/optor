#include <cmath>
#include <cassert>

#include "piska/Circle.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/math/rect.hpp"

#include "piska/Global.hpp"

optor::pp::Circle::Circle(dr4::Window* dr4Window, const ::pp::ControlsTheme& theme, ::pp::State* state) 
    :   circle_{dr4Window->CreateCircle()},
        isDragged_(false),
        state_{state},
        isResized_(false),
        selectRect_(dr4Window->CreateRectangle())
{
    circle_->SetRadius(1);
    circle_->SetBorderThickness(-10);
    circle_->SetBorderColor(theme.shapeColor);
    circle_->SetFillColor({0, 0, 0, 0});

    selectRect_->SetBorderThickness(-OutlineThickness);
    selectRect_->SetBorderColor(theme.lineColor);
    selectRect_->SetFillColor({0, 0, 0, 0});

    UpdateSelectRect();
}

bool optor::pp::Circle::OnMouseDown(const dr4::Event::MouseButton &evt) {
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

bool optor::pp::Circle::OnMouseUp(const dr4::Event::MouseButton &evt) {
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

bool optor::pp::Circle::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (isDragged_) {
        SetPos(circle_->GetPos() + evt.rel);
        return true;
    }

    if (isResized_) {
        ResizeBySide(evt.rel);
        return true;
    }

    return false;
}

void optor::pp::Circle::OnSelect() {
    if (state_->selectedShape != nullptr) {
        state_->selectedShape->OnDeselect();
    }
    state_->selectedShape = this;
}

void optor::pp::Circle::OnDeselect() {
}

void optor::pp::Circle::DrawOn(::dr4::Texture& texture) const {
    circle_->DrawOn(texture);

    if (state_->selectedShape == this) {
        selectRect_->DrawOn(texture);
    }
}

void optor::pp::Circle::SetPos(::dr4::Vec2f pos) {
    circle_->SetPos(pos);
    selectRect_->SetPos(pos);
}

::dr4::Vec2f optor::pp::Circle::GetPos() const {
    return circle_->GetPos();
}


void optor::pp::Circle::SetRadius(float radius) {
    circle_->SetRadius(radius);
    UpdateSelectRect();
}

bool optor::pp::Circle::OnMe(dr4::Vec2f relCoord) const {
    float distance = DistanceFromCenter2(relCoord);
    float rad = circle_->GetRadius();
    return distance <= rad * rad;
}

bool optor::pp::Circle::OnOutline(dr4::Vec2f relCoord) const {
    const dr4::Vec2f posOut = selectRect_->GetPos();
    const dr4::Vec2f sizeOut = selectRect_->GetSize();

    const dr4::Vec2f posIn = posOut + OutlineThicknessVec;
    const dr4::Vec2f sizeIn = sizeOut - 2 * OutlineThicknessVec;
    
    return dr4::Rect2f(posOut, sizeOut).Contains(relCoord) 
       && !dr4::Rect2f(posIn,  sizeIn) .Contains(relCoord);
}

float optor::pp::Circle::DistanceFromCenter2(dr4::Vec2f relCoord) const {
    dr4::Vec2f center = circle_->GetPos() + dr4::Vec2f{circle_->GetRadius(), circle_->GetRadius()};
    dr4::Vec2f dist = relCoord - center;
    return dist.x * dist.x + dist.y * dist.y;
}

void optor::pp::Circle::UpdateSelectRect() {
    selectRect_->SetPos(circle_->GetPos());

    const float radius2 = 2 * circle_->GetRadius();
    selectRect_->SetSize({radius2, radius2});
}


optor::pp::Side optor::pp::Circle::ClosestSide(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos  = circle_->GetPos();
    const dr4::Vec2f size = selectRect_->GetSize();

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

void optor::pp::Circle::ResizeBySide(dr4::Vec2f offset) {
    dr4::Vec2f pos  = circle_->GetPos();
    float radius = circle_->GetRadius();

    switch (activeSide_) {

        case Side::LEFT: {
            float newRadius = radius - offset.x / 2;
            if (newRadius > 0.0f) {
                radius = newRadius;
                pos.x += offset.x;
            }
            break;
        }

        case Side::RIGHT: {
            float newRadius = radius + offset.x / 2;
            if (newRadius > 0.0f) {
                radius = newRadius;
            }
            break;
        }

        case Side::TOP: {
            float newRadius = radius - offset.y / 2;
            if (newRadius > 0.0f) {
                radius = newRadius;
                pos.y += offset.y;
            }
            break;
        }

        case Side::BOTTOM: {
            float newRadius = radius + offset.y / 2;
            if (newRadius > 0.0f) {
                radius = newRadius;
            }
            break;
        }

        case Side::UNKNOWN:
        default:
            return;
    }

    circle_->SetPos(pos);
    circle_->SetRadius(radius);

    UpdateSelectRect();
}