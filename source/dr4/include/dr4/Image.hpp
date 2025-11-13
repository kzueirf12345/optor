#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP

#include <SFML/Graphics/Image.hpp>

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Image final: public ::dr4::Image { 

public:

    Image();
    
    virtual void SetPixel(size_t x, size_t y, ::dr4::Color color) override;
    virtual ::dr4::Color GetPixel(size_t x, size_t y) const override;

    virtual void SetSize(::dr4::Vec2f size) override;
    virtual ::dr4::Vec2f GetSize() const override;
    virtual float GetWidth() const override;
    virtual float GetHeight() const override;

    virtual void DrawOn(::dr4::Texture& texture) const override;

    virtual void SetPos(::dr4::Vec2f pos) override;

    virtual ::dr4::Vec2f GetPos() const override;

protected:
private:
    sf::Image image_;

    ::dr4::Vec2f pos_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP*/