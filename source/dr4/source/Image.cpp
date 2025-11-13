#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <cassert>

#include "dr4/Image.hpp"
#include "dr4/Texture.hpp"

#include "common/ErrorHandler.hpp"

optor::dr4::Image::Image() 
    :   image_{},
        pos_{}
{}

void optor::dr4::Image::SetPixel(size_t x, size_t y, ::dr4::Color color) {
    ERROR_HANDLE([&](){
        image_.setPixel(x, y, {color.r, color.g, color.b, color.a});
    });
}
::dr4::Color optor::dr4::Image::GetPixel(size_t x, size_t y) const {
    const sf::Color colorSF = image_.getPixel(x, y);
    return {colorSF.r, colorSF.g, colorSF.b, colorSF.a};
}

void optor::dr4::Image::SetSize(::dr4::Vec2f size) {
    ERROR_HANDLE([&](){
        image_.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
    });
}

::dr4::Vec2f optor::dr4::Image::GetSize() const {
    const sf::Vector2u sizeSF = image_.getSize();
    return {static_cast<float>(sizeSF.x), static_cast<float>(sizeSF.y)};
}
float optor::dr4::Image::GetWidth() const {
    const sf::Vector2u sizeSF = image_.getSize();
    return sizeSF.x;
}
float optor::dr4::Image::GetHeight() const {
    const sf::Vector2u sizeSF = image_.getSize();
    return sizeSF.y;
}

void optor::dr4::Image::DrawOn(::dr4::Texture& texture) const {
    sf::Texture textureSF = {}; // TODO smart redraw

    ERROR_HANDLE([&textureSF, this](){
        textureSF.loadFromImage(image_);
    });

    sf::Sprite spriteSF = ERROR_HANDLE([&textureSF](){
        return sf::Sprite(textureSF);
    });

    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([&spriteSF, this, &myTexture](){
        spriteSF.setPosition(pos_.x + myTexture.zero_.x, pos_.y + myTexture.zero_.y);
    });


    ERROR_HANDLE([&myTexture, &spriteSF](){
        myTexture.renderTexture_.draw(spriteSF);
    });

    ERROR_HANDLE([&myTexture](){
        myTexture.renderTexture_.display();
    });
}

void optor::dr4::Image::SetPos(::dr4::Vec2f pos) {
    pos_ = pos;
}

::dr4::Vec2f optor::dr4::Image::GetPos() const {
    return pos_;
}