#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "dr4/Font.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/texture.hpp"

#include "common/ErrorHandler.hpp"

dr4::Rect2f dr4::Text::GetBounds() const
{
    const sf::Font& fontSF = dynamic_cast<const optor::dr4::Font*>(font)->font_;

    sf::Text textSF(text, fontSF, fontSize);

    sf::FloatRect rectSF =  ERROR_HANDLE([&textSF](){
        return textSF.getLocalBounds();
    });

    return {rectSF.left, rectSF.top, rectSF.width, rectSF.height};
}