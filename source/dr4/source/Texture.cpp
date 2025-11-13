#include <SFML/Graphics/RenderTexture.hpp>
#include <cstdlib>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include "dr4/Texture.hpp"

#include "common/ErrorHandler.hpp"

optor::dr4::Texture::Texture()
    :   renderTexture_{},
        pos_{},
        zero_{},
        sprite_()
{
}

void optor::dr4::Texture::SetSize(::dr4::Vec2f size) 
{
    ERROR_HANDLE([this, &size](){
        renderTexture_.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
        renderTexture_.clear();
    });
    Redraw();
}

::dr4::Vec2f optor::dr4::Texture::GetSize() const 
{
    const sf::Vector2u sizeSF = ERROR_HANDLE([this](){
        return renderTexture_.getSize();
    });

    return {static_cast<float>(sizeSF.x), static_cast<float>(sizeSF.y)};
}

float optor::dr4::Texture::GetWidth() const 
{
    const sf::Vector2u sizeSF = ERROR_HANDLE([this](){
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

void optor::dr4::Texture::Clear(::dr4::Color color) {
    ERROR_HANDLE([this, &color](){
        renderTexture_.clear({color.r, color.g, color.b, color.a});
    });
    Redraw();
}

void optor::dr4::Texture::SetZero(::dr4::Vec2f pos) {
    zero_ = pos;
}
::dr4::Vec2f optor::dr4::Texture::GetZero() const {
    return zero_;
}

void optor::dr4::Texture::DrawOn(::dr4::Texture& texture) const {
    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([this, &myTexture](){
        myTexture.renderTexture_.draw(
            sprite_,
            sf::RenderStates().transform.translate(
                pos_.x + myTexture.zero_.x, 
                pos_.y + myTexture.zero_.y
            )
        );
    });

    ERROR_HANDLE([this, &myTexture](){
        myTexture.renderTexture_.display();
    });
}

void optor::dr4::Texture::SetPos(::dr4::Vec2f pos) {
    pos_ = pos;
}

::dr4::Vec2f optor::dr4::Texture::GetPos() const {
    return pos_;
}


void optor::dr4::Texture::Redraw() {
    sprite_ = ERROR_HANDLE([this](){
        return sf::Sprite(renderTexture_.getTexture());
    });
}