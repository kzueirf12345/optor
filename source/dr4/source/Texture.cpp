#include <stdexcept>
#include <cstdlib>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include "dr4/Texture.hpp"
#include "dr4/Font.hpp"
#include "dr4/texture.hpp"

#include "common/ErrorHandler.hpp"

void optor::dr4::Texture::SetSize(::dr4::Vec2f size) 
{
    ERROR_HANDLE([&](){
        renderTexture_.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
        renderTexture_.clear();
    });
}

::dr4::Vec2f optor::dr4::Texture::GetSize() const 
{
    const sf::Vector2u sizeSF = ERROR_HANDLE([&](){
        return renderTexture_.getSize();
    });

    return {static_cast<float>(sizeSF.x), static_cast<float>(sizeSF.y)};
}

float optor::dr4::Texture::GetWidth() const 
{
    const sf::Vector2u sizeSF = ERROR_HANDLE([&](){
        return renderTexture_.getSize();
    });

    return static_cast<float>(sizeSF.x);
}

float optor::dr4::Texture::GetHeight() const 
{
    const sf::Vector2u sizeSF = ERROR_HANDLE([this](){
        return renderTexture_.getSize();
    });

    return static_cast<float>(sizeSF.y);
}


void optor::dr4::Texture::Draw(const ::dr4::Rectangle &rect) 
{
    const sf::Vector2f sizeSF = {rect.rect.size.x, rect.rect.size.y};
    sf::RectangleShape rectSF(sizeSF);

    ERROR_HANDLE([this, &rectSF, &rect](){
        rectSF.setPosition(rect.rect.pos.x, rect.rect.pos.y);
    });

    ERROR_HANDLE([this, &rectSF, &rect](){
        rectSF.setFillColor(sf::Color(rect.fill.r, rect.fill.g, rect.fill.b, rect.fill.a));
    });

    ERROR_HANDLE([this, &rectSF, &rect](){
        rectSF.setOutlineColor(sf::Color(rect.borderColor.r, rect.borderColor.g, rect.borderColor.b, rect.borderColor.a));
    });

    ERROR_HANDLE([this, &rectSF, &rect](){
        rectSF.setOutlineThickness(rect.borderThickness);
    });

    ERROR_HANDLE([this, &rectSF](){
        renderTexture_.draw(rectSF);
    });

    ERROR_HANDLE([this](){
        renderTexture_.display();
    });
}

void optor::dr4::Texture::Draw(const ::dr4::Text &text) 
{
    sf::Text textSF(text.text, dynamic_cast<const optor::dr4::Font*>(text.font)->font_, text.fontSize);

    ERROR_HANDLE([this, &textSF, &text](){
        textSF.setFillColor(sf::Color(text.color.r, text.color.g, text.color.b, text.color.a));
    });

    const sf::FloatRect bounds = textSF.getLocalBounds();

    sf::Vector2f posSF = {text.pos.x, text.pos.y};
    
    switch(text.valign) {
        case ::dr4::Text::VAlign::TOP: {
            break;
        }
        case ::dr4::Text::VAlign::MIDDLE: {
            posSF.y -= bounds.height / 2.;
            break;
        }
        case ::dr4::Text::VAlign::BASELINE: {
            
            break;
        }
        case ::dr4::Text::VAlign::BOTTOM: {
            posSF.y -= bounds.height;
            break;
        }    

        case ::dr4::Text::VAlign::UNKNOWN:
        default:
            throw std::overflow_error("Unknown vertical align");
    }

    ERROR_HANDLE([&textSF, &posSF](){
        textSF.setPosition(posSF);
    });

    ERROR_HANDLE([this, &textSF](){
        renderTexture_.draw(textSF);
    });

    ERROR_HANDLE([this](){
        renderTexture_.display();
    });
}

void optor::dr4::Texture::Draw(const ::dr4::Image &image, const ::dr4::Vec2f& pos)
{
    sf::Image imageSF = {};

    ERROR_HANDLE([&imageSF, &image](){
        imageSF.create(image.GetSize().x, image.GetSize().y, image.GetArray());
    });

    sf::Texture textureSF = {};

    ERROR_HANDLE([&textureSF, &imageSF](){
        textureSF.loadFromImage(imageSF);
    });

    sf::Sprite spriteSF = ERROR_HANDLE([&textureSF](){
        return sf::Sprite(textureSF);
    });

    ERROR_HANDLE([&spriteSF, &pos](){
        spriteSF.setPosition(pos.x, pos.y);
    });

    ERROR_HANDLE([this, &spriteSF](){
        renderTexture_.draw(spriteSF);
    });

    ERROR_HANDLE([this](){
        renderTexture_.display();
    });
}

void optor::dr4::Texture::Draw(const ::dr4::Texture &texture, const ::dr4::Vec2f &pos) 
{
    const sf::Texture textureSF = ERROR_HANDLE([&texture](){
        return dynamic_cast<const optor::dr4::Texture&>(texture).renderTexture_.getTexture();
    });

    sf::Sprite spriteSF = ERROR_HANDLE([&textureSF](){
        return sf::Sprite(textureSF);
    });

    ERROR_HANDLE([&spriteSF, &pos](){
        spriteSF.setPosition(pos.x, pos.y);
    });

    ERROR_HANDLE([this, &spriteSF](){
        renderTexture_.draw(spriteSF);
    });

    ERROR_HANDLE([this](){
        renderTexture_.display();
    });
}