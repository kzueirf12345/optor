#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_CIRCLE_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_CIRCLE_HPP

#include <memory>
#include <cmath>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "pp/canvas.hpp"
#include "pp/shape.hpp"

#include "piska/Global.hpp"

namespace optor 
{
namespace pp 
{


class Circle final: public ::pp::Shape {

public:

    Circle(::pp::Canvas* cvs);

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

    virtual void OnSelect() override;
    virtual void OnDeselect() override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;
    virtual ::dr4::Vec2f GetPos() const override;

    void SetRadius(::dr4::Vec2f radius);

private:

    std::unique_ptr<dr4::Circle> circle_;
    std::unique_ptr<dr4::Rectangle> selectRect_;

    ::pp::Canvas* const cvs_;

    bool isResized_;
    Side activeSide_;

    bool isDragged_;

private:

    bool OnMe(dr4::Vec2f relCoord) const;
    bool OnOutline(dr4::Vec2f relCoord) const;
    Side ClosestSide(dr4::Vec2f relCoord) const;

    void UpdateSelectRect();

    void ResizeBySide(dr4::Vec2f offset);

    ::dr4::Vec2f DistanceFromCenter2(dr4::Vec2f relCoord) const;

};

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_CIRCLE_HPP*/