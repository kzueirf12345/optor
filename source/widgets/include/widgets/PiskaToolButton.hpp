#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_PISKA_TOOL_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_PISKA_TOOL_BUTTON_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

#include "pp/tool.hpp"
#include "widgets/WidgetButton.hpp"
#include "widgets/Textable.hpp"

namespace optor 
{

class PiskaToolButton: public WidgetButton, public Textable {
    public:
        PiskaToolButton(const dr4::Vec2f& size, optor::WidgetsState* state, pp::Tool* tool, pp::Tool** selectedTool);

        virtual void SetPosition(const dr4::Vec2f& position) override;

        virtual bool OnMousePress  (const ::dr4::Event& event) override;
        virtual bool OnMouseRelease(const ::dr4::Event& event) override;
        virtual bool OnKeyboardPress(const dr4::Event& event) override;

        virtual void OnIdle() override;

        virtual void Draw(dr4::Texture &srcTexture) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "PiskaToolButton"; };

    private:

        std::unique_ptr<dr4::Texture> texture_;
        pp::Tool* const tool_;

        pp::Tool** selectedTool_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_PISKA_TOOL_BUTTON_HPP*/