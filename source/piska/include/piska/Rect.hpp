#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_RECT_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_RECT_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "pp/canvas.hpp"
#include "pp/shape.hpp"

#include "piska/Global.hpp"

namespace optor 
{
namespace pp 
{

class Rect final: public ::pp::Shape {

public:

    Rect(::pp::Canvas* cvs);

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

    virtual void OnSelect() override;
    virtual void OnDeselect() override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

    void SetSize(dr4::Vec2f size);

private:

    std::unique_ptr<dr4::Rectangle> rect_;
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

};

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_RECT_HPP*/