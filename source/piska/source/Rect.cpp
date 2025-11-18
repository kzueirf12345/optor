#include <cmath>
#include <cassert>

#include "piska/Rect.hpp"
#include "dr4/math/rect.hpp"

optor::pp::Rect::Rect(dr4::Window* dr4Window, const ::pp::ControlsTheme& theme, ::pp::State* state) 
    :   rect_{dr4Window->CreateRectangle()},
        isDragged_(false),
        state_{state},
        selectRect_(dr4Window->CreateRectangle())
{
    rect_->SetSize({1, 1});
    rect_->SetBorderThickness(-10);
    rect_->SetBorderColor(theme.shapeColor);
    rect_->SetFillColor({0, 0, 0, 0});

    selectRect_->SetBorderThickness(-2 * OutlineThickness);
    selectRect_->SetBorderColor(theme.lineColor);
    selectRect_->SetFillColor({0, 0, 0, 0});

    UpdateSelectRect();
}

bool optor::pp::Rect::OnMouseDown(const dr4::Event::MouseButton &evt) {
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

bool optor::pp::Rect::OnMouseUp(const dr4::Event::MouseButton &evt) {

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

bool optor::pp::Rect::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (isDragged_) {
        SetPos(rect_->GetPos() + evt.rel);
        return true;
    }

    if (isResized_) {
        ResizeBySize(evt.rel);
        return true;
    }

    return false;
}


void optor::pp::Rect::OnSelect() {
    if (state_->selectedShape != nullptr) {
        state_->selectedShape->OnDeselect();
    }
    state_->selectedShape = this;
}

void optor::pp::Rect::OnDeselect() {
    
}


void optor::pp::Rect::DrawOn(::dr4::Texture& texture) const {
    rect_->DrawOn(texture);

    if (state_->selectedShape == this) {
        selectRect_->DrawOn(texture);
    }
}


void optor::pp::Rect::SetPos(::dr4::Vec2f pos) {
    rect_->SetPos(pos);
    selectRect_->SetPos(pos);
}


::dr4::Vec2f optor::pp::Rect::GetPos() const {
    return rect_->GetPos();;
}

void optor::pp::Rect::SetSize(dr4::Vec2f size) {
    rect_->SetSize({std::fabs(size.x), std::fabs(size.y)});

    UpdateSelectRect();
}


bool optor::pp::Rect::OnMe(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = rect_->GetPos();

    const dr4::Vec2f size = rect_->GetSize();

    return dr4::Rect2f(pos, size).Contains(relCoord);
}

bool optor::pp::Rect::OnOutline(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = rect_->GetPos();
    const dr4::Vec2f size = rect_->GetSize();

    const dr4::Vec2f posOut = pos - OutlineThicknessVec;
    const dr4::Vec2f sizeOut = size + 2 * OutlineThicknessVec;

    const dr4::Vec2f posIn = pos + OutlineThicknessVec;
    const dr4::Vec2f sizeIn = size - 2 * OutlineThicknessVec;
    
    return dr4::Rect2f(posOut, sizeOut).Contains(relCoord) 
       && !dr4::Rect2f(posIn,  sizeIn) .Contains(relCoord);
}

optor::pp::Side optor::pp::Rect::ClosestSide(dr4::Vec2f relCoord) const {
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

void optor::pp::Rect::ResizeBySize(dr4::Vec2f offset) {
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

    UpdateSelectRect();
}


void optor::pp::Rect::UpdateSelectRect()
{
    selectRect_->SetPos(rect_->GetPos());
    selectRect_->SetSize(rect_->GetSize());
}