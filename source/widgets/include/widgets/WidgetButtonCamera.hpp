#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_CAMERA_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_CAMERA_HPP

#include "hui/Color.hpp"
#include "optics/Camera.hpp"
#include "widgets/WidgetButton.hpp"

namespace optor 
{

class WidgetButtonCamera: public WidgetButton {
    public:
        WidgetButtonCamera(hui::RectangleShape rect, optor::WidgetsState* state, 
                           optor::Camera* camera, MoveDirection dir);
        
        virtual void OnIdle() override;

    private:

        optor::Camera* camera_;
        MoveDirection dir_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_CAMERA_HPP*/