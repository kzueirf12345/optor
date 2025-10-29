#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP

#include "hui/Color.hpp"
#include "hui/Vector.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetButton: public Widget {
    public:
        WidgetButton(const hui::Vector2d& size, optor::WidgetsState* state);
        
        virtual bool OnMousePress  (const hui::Event& event) override;
        virtual bool OnMouseRelease(const hui::Event& event) override;

        void SetReleasedColor(const hui::Color& color);
        void SetPressedColor (const hui::Color& color);

        bool IsPressed() const noexcept;
        
    protected:
        bool isPressed_;
        hui::Event::MouseButton pressButton_;

        hui::Color  pressedColor_;
        hui::Color releasedColor_;

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP*/