#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGETS_STATE_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGETS_STATE_HPP


#include <deque>
#include <memory>

#include "cum/ifc/pp.hpp"
#include "dr4/math/vec2.hpp"

#include "dr4/window.hpp"
#include "optics/OpticObj.hpp"

namespace optor 
{

class Widget;

struct WidgetsState {
    dr4::Window* window;
    std::vector<cum::PPToolPlugin*> piskaPlugins;

    const optor::Widget* hoveredWidget;
    const optor::Widget* draggedWidget;
    const optor::Widget* selectedWidget;
    dr4::Vec2f           prevMouseCoord;

    optor::OpticObj* selectedObj;

    std::deque<std::unique_ptr<optor::Widget>> modalWidgets;

    bool needUpdateScene;

    size_t objCounter;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGETS_STATE_HPP*/