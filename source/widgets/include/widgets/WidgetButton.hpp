#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP

#include "dr4/math/color.hpp"
#include "dr4/mousecodes.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetButton: public Widget {
    public:
        WidgetButton(const ::dr4::Vec2f& size, optor::WidgetsState* state);
        
        virtual bool OnMousePress  (const ::dr4::Event& event) override;
        virtual bool OnMouseRelease(const ::dr4::Event& event) override;

        void SetReleasedColor(const ::dr4::Color& color);
        void SetPressedColor (const ::dr4::Color& color);

        bool IsPressed() const noexcept;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetButton"; };
        
    protected:
        bool isPressed_;
        ::dr4::MouseCode pressButton_;

        ::dr4::Color  pressedColor_;
        ::dr4::Color releasedColor_;

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP*/