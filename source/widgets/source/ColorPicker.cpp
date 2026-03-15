#include <algorithm>
#include <cmath>
#include <cassert>

#include "widgets/ColorPicker.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/math/rect.hpp"

#include "pp/canvas.hpp"
#include "widgets/Widget.hpp"

optor::ColorPicker::ColorPicker(const dr4::Vec2f &size, optor::WidgetsState *state, pp::ControlsTheme* theme) 
    :   Widget(size, state),
        texture_(state->window->CreateTexture()),
        theme_{theme},
        colorRect_{state->window->CreateImage()},
        colorPoint_{state->window->CreateCircle()},
        hueRect_{state->window->CreateImage()},
        hueLine_{state->window->CreateLine()},
        hue_{0},
        saturation_{1},
        value_{1},
        isPointDragged_{false},
        isLineDragged_{false}
{
    ERROR_HANDLE([this, &size](){
        texture_->SetSize(size);
    });

    const float thikness = GetOutlineThickness();

    const dr4::Vec2f inSize = size - 2 * dr4::Vec2f{thikness, thikness};

    texture_->SetZero({thikness, thikness});

    colorRect_->SetSize({inSize.y, inSize.y});

    colorPoint_->SetRadius(8.f);
    colorPoint_->SetFillColor(theme->handleColor);
    colorPoint_->SetBorderThickness(2.0f);
    colorPoint_->SetBorderColor({255, 255, 255, 255});
    colorPoint_->SetCenter(colorRect_->GetSize());

    hueRect_->SetSize({inSize.x - inSize.y, inSize.y});
    hueRect_->SetPos(dr4::Vec2f{inSize.y, 0});

    hueLine_->SetColor(theme->handleColor);
    hueLine_->SetThickness(5);
    hueLine_->SetStart({inSize.y, 0});
    hueLine_->SetEnd({inSize.x, 0});

    for (size_t y = 0; y < inSize.y; ++y) {
        for (size_t x = 0; x < inSize.x - inSize.y; ++x) {
            hueRect_->SetPixel(x, y, HSV2RGB(static_cast<float>(y) / inSize.y * 360.f, 1, 1));
        }
    }

    UpdateHSV();
    UpdateColorRect();
}

void optor::ColorPicker::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

bool optor::ColorPicker::OnMousePress(const dr4::Event &evt) {

    if (isHide_) return false;

    const dr4::Vec2f pos = evt.mouseButton.pos - AbsCoord() - dr4::Vec2f{10, 10};
    if (evt.mouseButton.button == dr4::MouseButtonType::LEFT) {
        if (OnColorPoint(pos)) {
            isPointDragged_ = true;
            return true;
        }
        if (OnHueLine(pos)) {
            isLineDragged_ = true;
            return true;
        }

        if (OnColorRect(pos)) {
            colorPoint_->SetCenter(pos);
            isPointDragged_ = true;
            UpdateHSV();
            return true;
        }

        if (OnHueRect(pos)) {
            const float hueLineStartX = hueLine_->GetStart().x;
            const float hueLineEndX = hueLine_->GetEnd().x;

            hueLine_->SetStart({hueLineStartX, pos.y});
            hueLine_->SetEnd({hueLineEndX, pos.y});

            isLineDragged_ = true;

            UpdateHSV();
            UpdateColorRect();
            return true;
        }

    }

    return optor::Widget::OnMousePress(evt);
}

bool optor::ColorPicker::OnMouseRelease(const dr4::Event &evt) {
    if (isHide_) return false;

    if (evt.mouseButton.button == dr4::MouseButtonType::LEFT) {
        if (isPointDragged_) {
            isPointDragged_ = false;
            return true;
        }

        if (isLineDragged_) {
            isLineDragged_ = false;
            return true;
        }
    }

    return optor::Widget::OnMouseRelease(evt);
}

bool optor::ColorPicker::OnMouseMove(const dr4::Event &evt) {
    if (isHide_) return false;

    if (isPointDragged_) {
        colorPoint_->SetCenter(
            (colorPoint_->GetCenter() + evt.mouseMove.rel).Clamped(
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

        const float newY = std::clamp(hueLineStart.y + evt.mouseMove.rel.y, 0.f, hueRect_->GetSize().y);

        hueLine_->SetStart({hueLineStart.x, newY});
        hueLine_->SetEnd({hueLineEnd.x, newY});

        UpdateHSV();
        UpdateColorRect();
        return true;
    }

    return optor::Widget::OnMouseMove(evt);
}

void optor::ColorPicker::Draw(::dr4::Texture& srcTexture) {
    if (isHide_) return;

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*colorRect_);
    });

    ERROR_HANDLE([this](){
        texture_->Draw(*colorPoint_);
    });

    ERROR_HANDLE([this](){
        texture_->Draw(*hueRect_);
    });

    ERROR_HANDLE([this](){
        texture_->Draw(*hueLine_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}


bool optor::ColorPicker::OnColorRect(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = colorRect_->GetPos();
    const dr4::Vec2f size = colorRect_->GetSize();
    return dr4::Rect2f(pos, size).Contains(relCoord);
}

bool optor::ColorPicker::OnColorPoint(dr4::Vec2f relCoord) const {
    dr4::Vec2f center = colorPoint_->GetCenter();
    dr4::Vec2f dist = relCoord - center;
    float distance2 = dist.x * dist.x + dist.y * dist.y;
    float radius2 = colorPoint_->GetRadius().x * colorPoint_->GetRadius().x;

    return distance2 <= radius2;
}

bool optor::ColorPicker::OnHueRect(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = hueRect_->GetPos();
    const dr4::Vec2f size = hueRect_->GetSize();
    return dr4::Rect2f(pos, size).Contains(relCoord);
}

bool optor::ColorPicker::OnHueLine(dr4::Vec2f relCoord) const {
    const dr4::Vec2f pos = hueLine_->GetPos() + hueLine_->GetStart() - dr4::Vec2f{0, hueLine_->GetThickness() / 2};
    const dr4::Vec2f size = {hueLine_->GetEnd().x - hueLine_->GetStart().x, hueLine_->GetThickness()};
    return dr4::Rect2f(pos, size).Contains(relCoord);
}

void optor::ColorPicker::UpdateHSV() {
    const dr4::Vec2f colorRectSize = colorRect_->GetSize();
    const dr4::Vec2f colorPointPos = colorPoint_->GetCenter() - colorRect_->GetPos();
    
    saturation_ = colorPointPos.x / colorRectSize.x;
    value_ = colorPointPos.y / colorRectSize.y;
    
    hue_ = 360.f * ((hueLine_->GetStart().y / hueRect_->GetSize().y));

    theme_->shapeBorderColor = HSV2RGB(hue_, saturation_, value_);
}

dr4::Color optor::ColorPicker::HSV2RGB(float hue, float saturation, float value) {
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

void optor::ColorPicker::UpdateColorRect() {
    const dr4::Vec2f size = colorRect_->GetSize();
    for (size_t y = 0; y < size.y; ++y) {
        for (size_t x = 0; x < size.x; ++x) {
            colorRect_->SetPixel(x, y, HSV2RGB(hue_, static_cast<float>(x) / size.x, static_cast<float>(y) / size.y));
        }
    }
}