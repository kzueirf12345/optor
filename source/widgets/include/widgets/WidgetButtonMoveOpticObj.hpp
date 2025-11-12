#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_MOVE_OPTIC_OBJ_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_MOVE_OPTIC_OBJ_HPP

#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "optics/Camera.hpp"
#include "optics/OpticObj.hpp"
#include "widgets/WidgetButton.hpp"
#include "widgets/Textable.hpp"


namespace optor 
{

class WidgetButtonMoveOpticObj: public WidgetButton, public Textable {
    public:
        WidgetButtonMoveOpticObj(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, 
                                 const std::string& text,
                                 optor::OpticObj* camera, MoveDirection dir);
        
        virtual void OnIdle() override;

        virtual void Draw(dr4::Texture &srcTexture) override;

        [[nodiscard]] virtual std::string GetTypeName() const override {return "WidgetButtonMoveOpticObj"; };

    private:
        std::unique_ptr<dr4::Texture> texture_;
        optor::OpticObj* obj_;
        MoveDirection dir_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_MOVE_OPTIC_OBJ_HPP*/