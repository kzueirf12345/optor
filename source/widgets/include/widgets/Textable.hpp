#ifndef OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP
#define OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP

#include "dr4/texture.hpp"
#include <memory>

namespace optor 
{

class Textable {
    public:
        Textable(const std::string& text);

        // virtual void Draw(dr4::Texture& srcTexture) = 0;

        ::dr4::Text* GetText();

        [[nodiscard]] virtual std::string GetTypeName() const {return "Textable"; };

    protected:
        std::unique_ptr<::dr4::Text> text_;
};

}

#endif /*OPTOR_SOURCE_WIDGETS_INCLUDE_WIDGETS_WIDGET_BUTTON_TEXT_HPP*/
