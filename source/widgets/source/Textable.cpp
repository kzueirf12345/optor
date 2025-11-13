#include <cassert>

#include "widgets/Textable.hpp"
#include "dr4/window.hpp"
#include "global/Global.hpp"

optor::Textable::Textable(const std::string& text, dr4::Window* window)
    :   text_{window->CreateText()}
{
    text_->SetText(text);
    text_->SetFont(optor::FONT);
    text_->SetColor(optor::color::TextPrimary);
}

::dr4::Text* optor::Textable::GetText() {
    return text_.get();
}