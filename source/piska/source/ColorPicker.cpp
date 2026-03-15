#include <algorithm>
#include <cmath>
#include <cassert>
#include <ratio>
#include "piska/ColorPicker.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/math/rect.hpp"

#include "piska/Global.hpp"

optor::pp::ColorPicker::ColorPicker(::pp::Canvas* cvs) 
    :   cvs_{cvs},
        rect_{cvs->GetWindow()->CreateRectangle()},
        colorRect_{cvs->GetWindow()->CreateImage()},
        colorPoint_{cvs->GetWindow()->CreateCircle()},
        hueRect_{cvs->GetWindow()->CreateImage()},
        hueLine_{cvs->GetWindow()->CreateLine()},
        hue_{0},
        saturation_{1},
        value_{1},
        isPointDragged_{false},
        isLineDragged_{false}
{
    const dr4::Vec2f size(400, 300);
    const dr4::Vec2f pos(400, 100);

    rect_->SetSize(size);
    rect_->SetBorderThickness(10);
    rect_->SetBorderColor(optor::pp::WindowBorder);
    rect_->SetFillColor(optor::pp::WindowBackground);
    rect_->SetPos(400, 100);

    colorRect_->SetSize({size.y, size.y});
    colorRect_->SetPos(pos);

    colorPoint_->SetRadius(8.f);
    colorPoint_->SetFillColor(cvs->GetControlsTheme().handleColor);
    colorPoint_->SetBorderThickness(2.0f);
    colorPoint_->SetBorderColor({255, 255, 255, 255});
    colorPoint_->SetCenter(pos + colorRect_->GetSize());

    hueRect_->SetSize({size.x - size.y, size.y});
    hueRect_->SetPos(pos + dr4::Vec2f{size.y, 0});

    hueLine_->SetColor(cvs->GetControlsTheme().handleColor);
    hueLine_->SetThickness(5);
    hueLine_->SetStart({size.y, 0});
    hueLine_->SetEnd({size.x, 0});
    hueLine_->SetPos(pos);

    for (size_t y = 0; y < size.y; ++y) {
        for (size_t x = 0; x < size.x - size.y; ++x) {
            hueRect_->SetPixel(x, y, HSV2RGB(static_cast<float>(y) / size.y * 360.f, 1, 1));
        }
    }

    UpdateHSV();
    UpdateColorRect();
}

bool optor::pp::ColorPicker::OnMouseDown(const dr4::Event::MouseButton &evt) {
    if (evt.button == dr4::MouseButtonType::LEFT) {
        OnSelect();

        if (OnColorPoint(evt.pos)) {
            isPointDragged_ = true;
            return true;
        }
        if (OnHueLine(evt.pos)) {
            isLineDragged_ = true;
            return true;
        }

        if (OnColorRect(evt.pos)) {
            colorPoint_->SetCenter(evt.pos);
            UpdateHSV();
            return true;
        }

        if (OnHueRect(evt.pos)) {
            const float hueLineStartX = hueLine_->GetStart().x;
            const float hueLineEndX = hueLine_->GetEnd().x;
            const dr4::Vec2f pos = hueLine_->GetPos();

            hueLine_->SetStart({hueLineStartX, evt.pos.y - pos.y});
            hueLine_->SetEnd({hueLineEndX, evt.pos.y - pos.y});

            UpdateHSV();
            UpdateColorRect();
            return true;
        }

    }

    return false;
}

bool optor::pp::ColorPicker::OnMouseUp(const dr4::Event::MouseButton &evt) {
    if (evt.button == dr4::MouseButtonType::LEFT) {
        if (isPointDragged_) {
            isPointDragged_ = false;
            return true;
        }

        if (isLineDragged_) {
            isLineDragged_ = false;
            return true;
        }
    }

    return false;
}

bool optor::pp::ColorPicker::OnMouseMove(const dr4::Event::MouseMove &evt) {
    if (isPointDragged_) {
        colorPoint_->SetCenter(
            (colorPoint_->GetCenter() + evt.rel).Clamped(
                colorRect_->GetPos(), 
                colorRect_->GetPos() + colorRect_->GetSize()
            )
        );
        UpdateHSV();
        return true;
    }

    if (isLineDragged_) {
        const dr4::Vec2f hueLineStart = hueLine_->GetStart();
        const dr4::Vec2f hueLineEnd = hueLine_->GetEnd();
        const dr4::Vec2f pos = hueLine_->GetPos();

        const float newY = std::clamp(hueLineStart.y + evt.rel.y, 0.f, hueRect_->GetSize().y);

        hueLine_->SetStart({hueLineStart.x, newY});
        hueLine_->SetEnd({hueLineEnd.x, newY});

        UpdateHSV();
        UpdateColorRect();
        return true;
    }

    return false;
}

void optor::pp::ColorPicker::OnSelect() {
    if (cvs_->GetSelectedShape() != nullptr) {
        cvs_->GetSelectedShape()->OnDeselect();
    }
    cvs_->SetSelectedShape(this);
}

void optor::pp::ColorPicker::OnDeselect() {
}

void optor::pp::ColorPicker::DrawOn(::dr4::Texture& texture) const {
    rect_->DrawOn(texture);
    colorRect_->DrawOn(texture);
    colorPoint_->DrawOn(texture);
    hueRect_->DrawOn(texture);
    hueLine_->DrawOn(texture);
}

void optor::pp::ColorPicker::SetPos(::dr4::Vec2f pos) {
    const dr4::Vec2f prevPos = GetPos();
    colorPoint_->SetPos(pos + colorPoint_->GetPos() - prevPos);
    hueLine_->SetPos(pos + hueLine_->GetPos() - prevPos);
    hueRect_->SetPos(pos + hueRect_->GetPos() - prevPos);
    rect_->SetPos(pos);
    colorRect_->SetPos(pos);
}

::dr4::Vec2f optor::pp::ColorPicker::GetPos() const {
    return rect_->GetPos();
}

dr4::Color optor::pp::ColorPicker::GetColor() const {
    return HSV2RGB(hue_, saturation_, value_);
}

bool optor::pp::ColorPicker::OnColorRect(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = colorRect_->GetPos();
    const dr4::Vec2f size = colorRect_->GetSize();
    return dr4::Rect2f(pos, size).Contains(relCoord);
}

bool optor::pp::ColorPicker::OnColorPoint(dr4::Vec2f relCoord) const {
    dr4::Vec2f center = colorPoint_->GetPos() + colorPoint_->GetRadius();
    dr4::Vec2f dist = relCoord - center;
    float distance2 = dist.x * dist.x + dist.y * dist.y;
    float radius2 = colorPoint_->GetRadius().x * colorPoint_->GetRadius().x;
    
    return distance2 <= radius2;
}

bool optor::pp::ColorPicker::OnHueRect(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = hueRect_->GetPos();
    const dr4::Vec2f size = hueRect_->GetSize();
    return dr4::Rect2f(pos, size).Contains(relCoord);
}

bool optor::pp::ColorPicker::OnHueLine(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = hueLine_->GetPos() + hueLine_->GetStart() - dr4::Vec2f{0, hueLine_->GetThickness() / 2};
    const dr4::Vec2f size = {hueLine_->GetEnd().x - hueLine_->GetStart().x, hueLine_->GetThickness()};
    return dr4::Rect2f(pos, size).Contains(relCoord);
}

void optor::pp::ColorPicker::UpdateHSV() {

    const dr4::Vec2f colorRectSize = colorRect_->GetSize();
    const dr4::Vec2f colorPointPos = colorPoint_->GetCenter() - colorRect_->GetPos();
    
    saturation_ = colorPointPos.x / colorRectSize.x;
    value_ = colorPointPos.y / colorRectSize.y;
    
    hue_ = 360.f * ((hueLine_->GetStart().y / hueRect_->GetSize().y));
}

dr4::Color optor::pp::ColorPicker::HSV2RGB(float hue, float saturation, float value) {
    if (saturation == 0) {
        return dr4::Color(value * 255, value * 255, value * 255, 255);
    }
    
    float h = hue / 60.0f;
    int sector = static_cast<int>(h);
    float fraction = h - sector;
    
    float p = value * (1.0f - saturation);
    float q = value * (1.0f - saturation * fraction);
    float t = value * (1.0f - saturation * (1.0f - fraction));
    
    float r, g, b;
    
    switch (sector) {
        case 0:
            r = value; g = t; b = p;
            break;
        case 1:
            r = q; g = value; b = p;
            break;
        case 2:
            r = p; g = value; b = t;
            break;
        case 3:
            r = p; g = q; b = value;
            break;
        case 4:
            r = t; g = p; b = value;
            break;
        case 5:
        default:
            r = value; g = p; b = q;
            break;
    }
    
    return dr4::Color(r * 255, g * 255, b * 255, 255);
}

void optor::pp::ColorPicker::UpdateColorRect() {
    const dr4::Vec2f size = colorRect_->GetSize();
    for (size_t y = 0; y < size.y; ++y) {
        for (size_t x = 0; x < size.x; ++x) {
            colorRect_->SetPixel(x, y, HSV2RGB(hue_, static_cast<float>(x) / size.x, static_cast<float>(y) / size.y));
        }
    }
}