#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <cstdlib>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include "dr4Plugin/Texture.hpp"

#include "common/ErrorHandler.hpp"
#include "dr4/texture.hpp"
#include "dr4Plugin/Image.hpp"

optor::dr4::Texture::Texture()
    :   renderTexture_{},
        pos_{},
        zero_{},
        sprite_(),
        isClipped_(false),
        clipRect_()
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

::dr4::Image* optor::dr4::Texture::GetImage() const 
{
    const sf::Texture textureSF = renderTexture_.getTexture();
    const sf::Image imageSF = textureSF.copyToImage();

    optor::dr4::Image* image = new Image();

    image->SetPos(pos_);

    const sf::Vector2u sizeSF = imageSF.getSize(); 
    image->SetSize({static_cast<float>(sizeSF.x), static_cast<float>(sizeSF.y)});

    for (size_t y = 0; y < sizeSF.y; ++y) {
        for (size_t x = 0; x < sizeSF.x; ++x) {
            const sf::Color pixel = imageSF.getPixel(x, y);
            image->SetPixel(x, y, ::dr4::Color(pixel.r, pixel.g, pixel.b, pixel.a));
        }
    }

    return image;
}

void optor::dr4::Texture::SetZero(::dr4::Vec2f pos) {
    zero_ = pos;
}
::dr4::Vec2f optor::dr4::Texture::GetZero() const {
    return zero_;
}

void optor::dr4::Texture::SetClipRect(::dr4::Rect2f rect) {
    isClipped_ = true;
    clipRect_ = rect;
}

void optor::dr4::Texture::RemoveClipRect() {
    isClipped_ = false;
}

::dr4::Rect2f optor::dr4::Texture::GetClipRect() const {
    if (!isClipped_) {
        return {};
    }

    return clipRect_;
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
}

void optor::dr4::Texture::SetPos(::dr4::Vec2f pos) {
    pos_ = pos;
}

::dr4::Vec2f optor::dr4::Texture::GetPos() const {
    return pos_;
}


void optor::dr4::Texture::Redraw() {
    ERROR_HANDLE([this](){
        renderTexture_.display();
    });

    sprite_ = ERROR_HANDLE([this](){
        if (isClipped_) {
            return sf::Sprite(
                renderTexture_.getTexture(), 
                sf::IntRect(clipRect_.pos.x, clipRect_.pos.y, clipRect_.size.x, clipRect_.size.y)
            );
        } else {
            return sf::Sprite(renderTexture_.getTexture());
        }
            
    });
}