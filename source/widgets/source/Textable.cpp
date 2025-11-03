#include <cassert>

#include "widgets/Textable.hpp"
#include "global/Global.hpp"

optor::Textable::Textable(const std::string& text)
    :   text_{.text = text, .pos = {0, 0}, .font = optor::FONT}
{
    text_.color = optor::color::TextPrimary;
}

::dr4::Text* optor::Textable::GetText() {
    return &text_;
}