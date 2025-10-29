#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_OPTIC_OBJS_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_OPTIC_OBJS_HPP

#include "optics/Scene.hpp"
#include "widgets/WidgetChildable.hpp"

namespace optor 
{

class WidgetOpticObjs : public WidgetChildable {
    public:
        WidgetOpticObjs(const hui::Vector2d& size, optor::WidgetsState* state, const optor::Scene& scene);

    private:

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_OPTIC_OBJS_HPP*/