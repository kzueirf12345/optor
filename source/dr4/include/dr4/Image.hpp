#ifndef OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP
#define OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP

#include <SFML/System/Vector2.hpp>

#include "dr4/texture.hpp"

namespace optor
{
namespace dr4 
{

class Image : public ::dr4::Image { 

public:

    virtual void Create(::dr4::Vec2f size, ::dr4::Image::ColorMode mode, ::dr4::Color color = {0, 0, 0, 0}) override;

    virtual ::dr4::Vec2f GetSize() const override;

    virtual void SetPixel(size_t x, size_t y, ::dr4::Color color) override;
    virtual ::dr4::Color GetPixel(size_t x, size_t y) const override;

    virtual const uint8_t* GetArray() const override;

protected:
private:

    sf::Vector2u size_;
    std::vector<uint8_t> pixels_;
    ::dr4::Image::ColorMode mode_;
};

}
}

#endif /*OPTOR_SOURCE_DR4_INCLUDE_DR4_IMAGE_HPP*/