#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXTURE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXTURE_HPP

#include <SFML/Graphics/RenderTexture.hpp>

#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Window;

class Texture : public ::dr4::Texture
{ 
public:
    friend optor::dr4::Window;

    virtual void SetSize(::dr4::Vec2f size) override;
    virtual ::dr4::Vec2f GetSize() const override;
    virtual float GetWidth() const override;
    virtual float GetHeight() const override;

    virtual void Draw(const ::dr4::Rectangle &rect) override;
    virtual void Draw(const ::dr4::Text &text) override;
    virtual void Draw(const ::dr4::Image &image, const ::dr4::Vec2f& pos) override;
    virtual void Draw(const ::dr4::Texture &texture, const ::dr4::Vec2f &pos) override;

protected:

private:
    sf::RenderTexture renderTexture_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_TEXTURE_HPP*/