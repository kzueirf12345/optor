#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "dr4/Texture.hpp"
#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Image : public ::dr4::Image { 

public:
    friend optor::dr4::Texture;
    
    virtual void SetPixel(unsigned x, unsigned y, ::dr4::Color color) override;
    virtual ::dr4::Color GetPixel(unsigned x, unsigned y) const override;

    virtual void SetSize(::dr4::Vec2f size) override;
    virtual ::dr4::Vec2f GetSize() const override;
    virtual float GetWidth() const override;
    virtual float GetHeight() const override;

protected:
private:

    sf::Vector2u size_;
    std::vector<uint8_t> pixels_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP*/