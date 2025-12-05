#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_TEXT_TOOL_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_TEXT_TOOL_HPP

#include "dr4/event.hpp"
#include "dr4/texture.hpp"
#include "piska/Text.hpp"
#include "pp/canvas.hpp"
#include "pp/tool.hpp"
#include <memory>

namespace optor 
{
namespace pp 
{

class TextTool final: public ::pp::Tool {

public:

    TextTool(dr4::Font* font, ::pp::Canvas* cvs);

    virtual std::string_view Icon() const override;
    virtual std::string_view Name() const override;
    virtual bool IsCurrentlyDrawing() const override;

    virtual void OnStart() override;
    virtual void OnBreak() override;
    virtual void OnEnd() override;

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) override;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) override;
    virtual bool OnKeyDown(const dr4::Event::KeyEvent &evt) override;
    virtual bool OnText(const dr4::Event::TextEvent &evt) override;

private:

    ::pp::Canvas* cvs_;

    bool isDrawing_;

    optor::pp::Text* text_;

    bool keyHandled_;

    dr4::Font* font_;

    mutable std::unique_ptr<dr4::Text> tempText_;

private:

    size_t FindLetterPos(float mousePosX) const;

    bool HandleTextFinish(const dr4::Event::KeyEvent& evt);
    bool HandleBackspace(const dr4::Event::KeyEvent& evt);
    bool HandleDelete(const dr4::Event::KeyEvent& evt);
    bool HandleArrowLeft(const dr4::Event::KeyEvent& evt);
    bool HandleArrowRight(const dr4::Event::KeyEvent& evt);
    bool HandleA(const dr4::Event::KeyEvent& evt);
    bool HandleC(const dr4::Event::KeyEvent& evt);
    bool HandleV(const dr4::Event::KeyEvent& evt);

};

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_TEXT_TOOL_HPP*/