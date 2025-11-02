#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGETS_STATE_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGETS_STATE_HPP


#include "dr4/math/vec2.hpp"

#include "optics/OpticObj.hpp"

namespace optor 
{

class Widget;

struct WidgetsState {

    const optor::Widget* hoveredWidget;
    const optor::Widget* draggedWidget;
    const optor::Widget* selectedWidget;
    dr4::Vec2f           prevMouseCoord;

    optor::OpticObj* selectedObj;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGETS_STATE_HPP*/