#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_LIST_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_LIST_HPP

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "widgets/ScrollBar.hpp"
#include "widgets/WidgetChildable.hpp"
#include <memory>

namespace optor 
{

class WidgetList : public WidgetChildable {
    public:
        WidgetList(dr4::Window* window, optor::WidgetsState* state);

        virtual optor::Widget* AddChild(std::unique_ptr<Widget> child) override;

    protected:

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_LIST_HPP*/