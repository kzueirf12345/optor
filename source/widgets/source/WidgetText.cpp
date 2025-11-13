#include "dr4/window.hpp"

#include "widgets/WidgetText.hpp"
#include "widgets/Textable.hpp"
#include "widgets/Widget.hpp"
#include "common/ErrorHandler.hpp"

optor::WidgetText::WidgetText(const dr4::Vec2f& size, optor::WidgetsState* state, const std::string& text)
    :   optor::Widget(size, state),
        optor::Textable(text, state->window),
        texture_{state->window->CreateTexture()}
{
    ERROR_HANDLE([this](){
        texture_->SetSize(rect_->GetSize());
    });

    ERROR_HANDLE([this, &size](){
        const dr4::Vec2f localBounds = text_->GetBounds();
        text_->SetPos((size.x - localBounds.x) / 2,
                      (size.y - localBounds.y) / 2);
    });
}

void optor::WidgetText::SetPosition(const dr4::Vec2f& position) {
    optor::Widget::SetPosition(position);
    texture_->SetPos(position);
}

void optor::WidgetText::Draw(dr4::Texture& srcTexture)
{
    if (isHide_) { return; }

    const dr4::Vec2f pos = rect_->GetPos();

    rect_->SetPos({0, 0});
    ERROR_HANDLE([this](){
        optor::Widget::Draw(*texture_);
    });
    rect_->SetPos(pos);

    ERROR_HANDLE([this](){
        texture_->Draw(*text_);
    });

    ERROR_HANDLE([this, &srcTexture](){
        srcTexture.Draw(*texture_);
    });
}

