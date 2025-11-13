#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXTURE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXTURE_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "dr4/Rectangle.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Window;

class Text;
class Image;
class Line;
class Circle;
class Rectangle;

class Texture final: public ::dr4::Texture { 

    friend optor::dr4::Window;

    friend optor::dr4::Text;
    friend optor::dr4::Image;
    friend optor::dr4::Line;
    friend optor::dr4::Circle;
    friend optor::dr4::Rectangle;

public:

    Texture();

    virtual void SetSize(::dr4::Vec2f size) override;
    virtual ::dr4::Vec2f GetSize() const override;

    virtual float GetWidth() const override;
    virtual float GetHeight() const override;

    virtual void SetZero(::dr4::Vec2f pos) override;
    virtual ::dr4::Vec2f GetZero() const override;

    virtual void Clear(::dr4::Color color) override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

private:

    sf::RenderTexture renderTexture_;
    ::dr4::Vec2f zero_;
    ::dr4::Vec2f pos_;

    sf::Sprite sprite_;

    void Redraw();
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXTURE_HPP*/