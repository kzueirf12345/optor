#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_LIST_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_LIST_HPP

#include "widgets/WidgetChildable.hpp"
#include <memory>

namespace optor 
{

class WidgetList : public WidgetChildable {
    public:
        WidgetList(optor::WidgetsState* state);

        virtual optor::Widget* AddChild(std::unique_ptr<Widget> child) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetList"; };

    protected:

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_LIST_HPP*/