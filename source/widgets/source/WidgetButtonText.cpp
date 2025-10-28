#include <cassert>

#include "widgets/WidgetButtonText.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Vector.hpp"
#include "widgets/WidgetButton.hpp"

optor::WidgetButtonText::WidgetButtonText(hui::RectangleShape rect, optor::WidgetsState* state, 
                                          const std::string& text)
    : optor::WidgetButton(std::move(rect), state),
      text_{text},
      textAlign_{hui::Text::Align::Center},
      textOffset_{0, 0}
{
    ERROR_HANDLE([this](){
        text_.SetFont(FONT);
        text_.SetFillColor(optor::color::TextPrimary);
    });
}

void optor::WidgetButtonText::SetTextAlign(hui::Text::Align align) noexcept {
    textAlign_ = align;
}

void optor::WidgetButtonText::SetTextOffset(const hui::Vector2d& offset) noexcept {
    textOffset_ = offset;
}

hui::Vector2d optor::WidgetButtonText::GetTextPosition() const {
    const hui::Vector2d buttonSize = rect_.GetSize();
    const hui::Vector2d textSize   = text_.GetSize();
    hui::Vector2d pos;

    switch (textAlign_) {
        case hui::Text::Align::TopLeft:
            pos = {0, 0};
            break;
        case hui::Text::Align::TopCenter:
            pos = {(buttonSize.x - textSize.x) / 2.0, 0};
            break;
        case hui::Text::Align::TopRight:
            pos = {buttonSize.x - textSize.x, 0};
            break;
        case hui::Text::Align::CenterLeft:
            pos = {0, (buttonSize.y - textSize.y) / 2.0};
            break;
        case hui::Text::Align::Center:
            pos = {(buttonSize.x - textSize.x) / 2.0, (buttonSize.y - textSize.y) / 2.0};
            break;
        case hui::Text::Align::CenterRight:
            pos = {buttonSize.x - textSize.x, (buttonSize.y - textSize.y) / 2.0};
            break;
        case hui::Text::Align::BottomLeft:
            pos = {0, buttonSize.y - textSize.y};
            break;
        case hui::Text::Align::BottomCenter:
            pos = {(buttonSize.x - textSize.x) / 2.0, buttonSize.y - textSize.y};
            break;
        case hui::Text::Align::BottomRight:
            pos = {buttonSize.x - textSize.x, buttonSize.y - textSize.y};
            break;
    }

    return pos - hui::Vector2d(0, rect_.GetOutlineThinkness()) + textOffset_;
}

void optor::WidgetButtonText::Draw(hui::Window* window) {
    assert(window);

    ERROR_HANDLE([this, window](){
        optor::WidgetButton::Draw(window);
    });

    const hui::Vector2d relCoord = GetTextPosition();
    const hui::Vector2d textCoord = text_.GetPosition();
    ERROR_HANDLE(&hui::Text::SetPosition, &text_, AbsCoord() + relCoord);

    ERROR_HANDLE([window, this](){
        window->Draw(text_);
    });

    ERROR_HANDLE(&hui::Text::SetPosition, &text_, textCoord);
}
