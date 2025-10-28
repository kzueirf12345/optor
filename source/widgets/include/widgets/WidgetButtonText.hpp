#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP

#include "hui/Text.hpp"
#include "optics/Camera.hpp"
#include "widgets/WidgetButton.hpp"

namespace optor 
{

class WidgetButtonText: public WidgetButton {
    public:

        WidgetButtonText(hui::RectangleShape rect, optor::WidgetsState* state, const std::string& text);

        virtual void Draw(hui::Window* window) override;

        void SetTextAlign(hui::Text::Align align) noexcept;
        void SetTextOffset(const hui::Vector2d& offset) noexcept;

    private:
        hui::Vector2d GetTextPosition() const;

    private:
        optor::Camera* camera_;
        MoveDirection dir_;

        hui::Text text_;
        hui::Text::Align textAlign_;
        hui::Vector2d textOffset_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP*/
