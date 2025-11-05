#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_TEXT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_TEXT_HPP

#include <memory>

#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetText: public Widget, public Textable {
public:
    WidgetText(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, const std::string& text);

    virtual void Draw(dr4::Texture& srcTexture) override;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetText"; };

protected:
    std::unique_ptr<dr4::Texture> texture_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_TEXT_HPP*/