#ifndef OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_RECT_HPP
#define OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_RECT_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "hui/geomprim.hpp"

namespace optor 
{
namespace geomprim 
{

enum Side {
    UNKNOWN = -1,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

class Rect final: public hui::GeomPrim {

public:

    Rect(dr4::Window* dr4Window);

    bool OnMouseMove(const dr4::Event& event)    override;
    bool OnMouseDown(const dr4::Event& event)    override;
    bool OnMouseRelease(const dr4::Event& event) override;

    virtual void DrawOn(dr4::Texture& texture) const override;

    virtual void SetPos(dr4::Vec2f pos) override;

    virtual dr4::Vec2f GetPos() const override;

private:

    std::unique_ptr<dr4::Rectangle> rect_;

    bool isResized_;
    Side activeSide_;

    bool isDragged_;

private:

    bool OnMe(dr4::Vec2f relCoord) const;
    bool OnBorder(dr4::Vec2f relCoord) const;
    bool OnOutline(dr4::Vec2f relCoord) const;
    Side ClosestSide(dr4::Vec2f relCoord) const;

    void Resize(dr4::Vec2f offset);

    
};

}
}

#endif /*OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_RECT_HPP*/