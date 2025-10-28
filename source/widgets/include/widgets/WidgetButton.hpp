#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP

#include "hui/Color.hpp"
#include "widgets/Widget.hpp"

namespace optor 
{

class WidgetButton: public Widget {
    public:
        WidgetButton(hui::RectangleShape rect, optor::WidgetsState* state);
        
        virtual bool OnMousePress  (const hui::Event& event) override;
        virtual bool OnMouseRelease(const hui::Event& event) override;

    protected:
        bool isPressed_;
        hui::Event::MouseButton pressButton_;

        hui::Color  pressedColor_;
        hui::Color releasedColor_;

    private:
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_HPP*/