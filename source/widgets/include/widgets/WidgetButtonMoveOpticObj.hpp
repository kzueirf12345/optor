#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_MOVE_OPTIC_OBJ_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_MOVE_OPTIC_OBJ_HPP

#include "hui/Vector.hpp"
#include "optics/Camera.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/WidgetButtonText.hpp"

namespace optor 
{

class WidgetButtonMoveOpticObj: public WidgetButtonText {
    public:
        WidgetButtonMoveOpticObj(const hui::Vector2d& size, optor::WidgetsState* state, const std::string& text,
                                 optor::OpticObj* obj, MoveDirection dir);
        
        virtual void OnIdle() override;

        void SetObj(optor::OpticObj* obj);

    private:
        optor::OpticObj* obj_;
        MoveDirection dir_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_MOVE_OPTIC_OBJ_HPP*/