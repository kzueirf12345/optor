#include <cassert>

#include "widgets/WidgetButtonText.hpp"
#include "global/Global.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Renderer.hpp"
#include "hui/Vector.hpp"
#include "widgets/WidgetButton.hpp"

optor::WidgetButtonText::WidgetButtonText(const hui::Vector2d& size, optor::WidgetsState* state, 
                                          const std::string& text)
    : optor::WidgetButton(size, state),
      text_{text},
      textAlign_{hui::Text::Align::Center},
      textOffset_{0, 0},
      renderer_(size)
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
    const hui::Vector2d buttonSize = texture_.GetSize();
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

    return pos + textOffset_;
}

void optor::WidgetButtonText::Draw(hui::Renderer* renderer) {
    assert(renderer);

    const hui::Vector2d pos = sprite_.GetPosition();

    sprite_.SetPosition({0, 0});
    ERROR_HANDLE([this](){
        optor::WidgetButton::Draw(&renderer_);
    });
    sprite_.SetPosition(pos);

    text_.SetPosition(GetTextPosition());

    ERROR_HANDLE([this](){
        renderer_.Draw(text_);
    });

    ERROR_HANDLE([this](){
        renderer_.Display();
    });

    hui::Sprite sprite = ERROR_HANDLE([this](){
        return hui::Sprite(ERROR_HANDLE(&hui::Renderer::GetTexture, renderer_));
    });

    ERROR_HANDLE(&hui::Sprite::SetPosition, &sprite, pos);

    ERROR_HANDLE(&hui::Renderer::Draw, renderer, sprite);
}
