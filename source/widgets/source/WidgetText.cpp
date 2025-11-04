#include "dr4/window.hpp"

#include "widgets/WidgetText.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetText::WidgetText(dr4::Window* window, const dr4::Vec2f& size, optor::WidgetsState* state, const std::string& text)
    :   optor::Widget(size, state),
        optor::Textable(text),
        texture_{window->CreateTexture()}
{
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_.rect.size);
    });
}

void optor::WidgetText::Draw(dr4::Texture& srcTexture)
{
    const dr4::Vec2f pos = rect_.rect.pos;

    rect_.rect.pos = {0, 0};
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_.rect.pos = pos;

    ERROR_HANDLE([this](){
        texture_->Draw(text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_, rect_.rect.pos);
    });
}

