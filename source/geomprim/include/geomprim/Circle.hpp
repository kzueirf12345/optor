#ifndef OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_CIRCLE_HPP
#define OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_CIRCLE_HPP

#include <memory>

#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "hui/geomprim.hpp"

#include "geomprim/Backend.hpp"

namespace optor
{
namespace geomprim
{

class Circle final: public hui::GeomPrim {

public:

    Circle(dr4::Window* dr4Window);

    bool OnMouseMove(const dr4::Event& event)    override;
    bool OnMouseDown(const dr4::Event& event)    override;
    bool OnMouseRelease(const dr4::Event& event) override;

    void DrawOn(dr4::Texture& texture) const override;

    void SetPos(dr4::Vec2f pos) override;
    dr4::Vec2f GetPos() const override;

private:

    std::unique_ptr<dr4::Circle> circle_;
    dr4::Rect2f rect_;

    bool isDragged_;

    Side activeSide_;
    bool isResized_;

private:

    bool OnMe(dr4::Vec2f relCoord) const;
    bool OnBorder(dr4::Vec2f relCoord) const;
    bool OnOutline(dr4::Vec2f relCoord) const;
    Side ClosestSide(dr4::Vec2f relCoord) const;

    void Resize(dr4::Vec2f offset);
};

}
}

#endif /* OPTOR_SOURCE_GEOMPRIM_INCLUDE_GEOMPRIM_CIRCLE_HPP */
