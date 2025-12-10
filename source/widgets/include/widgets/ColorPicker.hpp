#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_COLOR_PICKER_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_COLOR_PICKER_HPP

#include <memory>
#include <cmath>

#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "pp/canvas.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class ColorPicker final: public Widget {

public:

    ColorPicker(const dr4::Vec2f& size, optor::WidgetsState *state, ::pp::ControlsTheme* theme);

    virtual bool OnMousePress(const dr4::Event &evt) override;
    virtual bool OnMouseRelease(const dr4::Event &evt) override;
    virtual bool OnMouseMove(const dr4::Event &evt) override;

    virtual void SetPosition(const dr4::Vec2f& position) override;

    virtual void Draw(::dr4::Texture& srcTexture) override;

    dr4::Color GetColor() const;

private:
    std::unique_ptr<dr4::Texture> texture_;

    std::unique_ptr<dr4::Image> colorRect_;
    std::unique_ptr<dr4::Circle> colorPoint_;

    std::unique_ptr<dr4::Image> hueRect_;
    std::unique_ptr<dr4::Line> hueLine_;

    float hue_;       
    float saturation_;
    float value_;

    ::pp::ControlsTheme* const theme_;

    bool isPointDragged_;
    bool isLineDragged_;

private:

    bool OnColorRect(dr4::Vec2f relCoord) const;
    bool OnColorPoint(dr4::Vec2f relCoord) const;
    bool OnHueRect(dr4::Vec2f relCoord) const;
    bool OnHueLine(dr4::Vec2f relCoord) const;

    void UpdateHSV();
    static dr4::Color HSV2RGB(float hue, float saturation, float value);
    void UpdateColorRect();

};

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_COLOR_PICKER_HPP*/