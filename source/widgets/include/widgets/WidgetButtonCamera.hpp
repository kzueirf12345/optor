#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_CAMERA_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_CAMERA_HPP

#include "optics/Camera.hpp"
#include "widgets/WidgetButtonText.hpp"

namespace optor 
{

class WidgetButtonCamera: public WidgetButtonText {
    public:
        WidgetButtonCamera(hui::RectangleShape rect, optor::WidgetsState* state, const std::string& text,
                           optor::Camera* camera, MoveDirection dir);
        
        virtual void OnIdle() override;

    private:
        optor::Camera* camera_;
        MoveDirection dir_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_CAMERA_HPP*/