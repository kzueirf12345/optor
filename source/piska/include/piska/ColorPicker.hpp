#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_COLOR_PICKER_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_COLOR_PICKER_HPP

#include <memory>
#include <cmath>

#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "pp/canvas.hpp"
#include "pp/shape.hpp"

namespace optor 
{
namespace pp 
{

class ColorPicker final: public ::pp::Shape {

public:

    ColorPicker(::pp::Canvas* cvs);

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

    virtual void OnSelect() override;
    virtual void OnDeselect() override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;
    virtual ::dr4::Vec2f GetPos() const override;

    dr4::Color GetColor() const;

private:
    std::unique_ptr<dr4::Rectangle> rect_;

    std::unique_ptr<dr4::Image> colorRect_;
    std::unique_ptr<dr4::Circle> colorPoint_;

    std::unique_ptr<dr4::Image> hueRect_;
    std::unique_ptr<dr4::Line> hueLine_;

    float hue_;       
    float saturation_;
    float value_;

    ::pp::Canvas* const cvs_;

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

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_COLOR_PICKER_HPP*/