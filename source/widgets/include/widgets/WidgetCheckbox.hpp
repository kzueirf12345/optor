#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHECKBOX_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHECKBOX_HPP

#include <memory>
#include <functional>

#include "dr4/texture.hpp"
#include "dr4/window.hpp"
#include "dr4/math/vec2.hpp"

#include "widgets/WidgetButton.hpp"

namespace optor 
{

class WidgetCheckbox: public WidgetButton {
    public:
        using ActionT = std::function<void(bool)>; 

        WidgetCheckbox(dr4::Window* window, const ::dr4::Vec2f& size, optor::WidgetsState* state, ActionT action, bool isPressed = true);
        
        virtual bool OnMousePress  (const ::dr4::Event& event) override;
        virtual bool OnMouseRelease(const ::dr4::Event& event) override;

        virtual void Draw(::dr4::Texture &srcTexture) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetCheckbox"; };

    private:
        std::unique_ptr<::dr4::Texture> texture_;

        ::dr4::Text pressedText_;
        ActionT action_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_CHECKBOX_HPP*/