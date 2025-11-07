#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_DESC_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_DESC_HPP


#include "dr4/math/vec2.hpp"
#include "dr4/window.hpp"

#include "optics/OpticObj.hpp"
#include "widgets/WidgetChildable.hpp"
#include "widgets/WidgetsState.hpp"
#include "widgets/WidgetHeader.hpp"
#include "widgets/WidgetList.hpp"
#include "widgets/WidgetScrolledList.hpp"

namespace optor 
{

class OpticObjDesc {
    public:
        OpticObjDesc(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, optor::OpticObj* obj);

        optor::WidgetHeader* operator()(optor::WidgetChildable* parent);

    private:
        dr4::Window* window_;
        dr4::Vec2f size_;
        optor::WidgetsState* state_;
        optor::OpticObj* obj_;

        optor::WidgetList* AddCoordInfo(optor::WidgetScrolledList* list);
        optor::WidgetList* AddColorInfo(optor::WidgetScrolledList* list);
        optor::WidgetList* AddMaterialFeatures(optor::WidgetScrolledList* list);

        static std::string FormatDouble(double value);

};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_OPTIC_OBJ_DESC_HPP*/