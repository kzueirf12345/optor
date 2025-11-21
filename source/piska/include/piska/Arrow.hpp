#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_ARROW_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_ARROW_HPP

#include <memory>
#include <cmath>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "pp/canvas.hpp"
#include "pp/shape.hpp"

#include "piska/Global.hpp"

namespace optor 
{
namespace pp 
{

class Arrow final: public ::pp::Shape {

public:

    Arrow(dr4::Window* dr4Window, const ::pp::ControlsTheme& theme, ::pp::State* state);

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

    virtual void OnSelect() override;
    virtual void OnDeselect() override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;
    virtual ::dr4::Vec2f GetPos() const override;

    void SetStart(::dr4::Vec2f start);
    void SetEnd(::dr4::Vec2f end);
    ::dr4::Vec2f GetStart() const;
    ::dr4::Vec2f GetEnd() const;

private:

    std::unique_ptr<dr4::Line> line_;
    std::unique_ptr<dr4::Line> leftTip_;
    std::unique_ptr<dr4::Line> rightTip_;
    std::unique_ptr<dr4::Rectangle> selectRect_;
    std::unique_ptr<dr4::Circle> startPoint_;
    std::unique_ptr<dr4::Circle> endPoint_;

    ::pp::State* const state_;

    bool isResized_;
    Side activeSide_;

    bool isDragged_;
    bool isStartPointDragged_;
    bool isEndPointDragged_;

private:

    bool OnMe(dr4::Vec2f relCoord) const;
    bool OnOutline(dr4::Vec2f relCoord) const;
    bool OnStartPoint(dr4::Vec2f relCoord) const;
    bool OnEndPoint(dr4::Vec2f relCoord) const;
    Side ClosestSide(dr4::Vec2f relCoord) const;

    void UpdateSelectRect();
    void UpdateTips();
    void UpdateControlPoints();

    void ResizeBySide(dr4::Vec2f offset);

    static dr4::Vec2f GetNormal(dr4::Vec2f vec);

};

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_ARROW_HPP*/