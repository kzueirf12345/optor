#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_HIDE_CHECKBOX_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_HIDE_CHECKBOX_HPP

#include "widgets/Widget.hpp"
#include "widgets/WidgetCheckbox.hpp"


namespace optor 
{

class HideCheckbox: public WidgetCheckbox {
public:
    HideCheckbox(const ::dr4::Vec2f& size, optor::WidgetsState* state, optor::Widget* widget);
    
    virtual void OnIdle() override;

    [[nodiscard]] virtual std::string GetTypeName() const override {return "HideCheckbox"; };

protected:
    optor::Widget* widget_;

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_HIDE_CHECKBOX_HPP*/