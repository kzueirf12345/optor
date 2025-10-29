#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP

#include "hui/Renderer.hpp"
#include "hui/Text.hpp"
#include "widgets/WidgetButton.hpp"

namespace optor 
{

class WidgetButtonText: public WidgetButton {
    public:

        WidgetButtonText(const hui::Vector2d& size, optor::WidgetsState* state, const std::string& text);

        virtual void Draw(hui::Renderer* renderer) override;

        void SetTextAlign(hui::Text::Align align) noexcept;
        void SetTextOffset(const hui::Vector2d& offset) noexcept;

    private:
        hui::Vector2d GetTextPosition() const;

    private:
        hui::Renderer renderer_;

        hui::Text text_;
        hui::Text::Align textAlign_;
        hui::Vector2d textOffset_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP*/
