#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_CIRCLE_TOOL_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_CIRCLE_TOOL_HPP

#include "dr4/math/vec2.hpp"
#include "piska/Circle.hpp"
#include "pp/canvas.hpp"
#include "pp/tool.hpp"

namespace optor 
{
namespace pp 
{

class CircleTool final: public ::pp::Tool {

public:

    CircleTool(::pp::Canvas* cvs);

    virtual std::string_view Icon() const override;
    virtual std::string_view Name() const override;
    virtual bool IsCurrentlyDrawing() const override;

    virtual void OnStart() override;
    virtual void OnBreak() override;
    virtual void OnEnd() override;

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;

private:

    ::pp::Canvas* cvs_;

    bool isDrawing_;

    optor::pp::Circle* circle_;

    ::dr4::Vec2f startPos_;

};

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_CIRCLE_TOOL_HPP*/