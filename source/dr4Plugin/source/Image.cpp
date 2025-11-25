#include <cassert>

#include <SFML/Graphics/RenderTexture.hpp>

#include "dr4Plugin/Image.hpp"
#include "dr4Plugin/Texture.hpp"
#include "common/ErrorHandler.hpp"


optor::dr4::Image::Image()
    : pixels_(sf::Points), size_{}, pos_{}
{}

void optor::dr4::Image::SetSize(::dr4::Vec2f size)
{
    ERROR_HANDLE([this, size]() {
        size_ = size;
        const size_t width  = static_cast<size_t>(size.x);
        const size_t height = static_cast<size_t>(size.y);
        const size_t total  = width * height;

        pixels_.setPrimitiveType(sf::Points);
        pixels_.resize(total);

        for (size_t y = 0; y < height; ++y)
        {
            for (size_t x = 0; x < width; ++x)
            {
                const size_t i = y * width + x;
                pixels_[i].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
                pixels_[i].color = sf::Color::Black;
            }
        }
    });
}

void optor::dr4::Image::SetPixel(size_t x, size_t y, ::dr4::Color color)
{
    ERROR_HANDLE([this, x, y, color]() {
        const size_t width = static_cast<size_t>(size_.x);
        const size_t index = y * width + x;
        assert(index < pixels_.getVertexCount());

        pixels_[index].color = sf::Color(color.r, color.g, color.b, color.a);
    });
}

::dr4::Color optor::dr4::Image::GetPixel(size_t x, size_t y) const
{
    const size_t width = static_cast<size_t>(size_.x);
    const size_t index = y * width + x;
    assert(index < pixels_.getVertexCount());

    const sf::Color colorSF = pixels_[index].color;
    return {colorSF.r, colorSF.g, colorSF.b, colorSF.a};
}

::dr4::Vec2f optor::dr4::Image::GetSize() const
{
    return size_;
}

float optor::dr4::Image::GetWidth() const
{
    return size_.x;
}

float optor::dr4::Image::GetHeight() const
{
    return size_.y;
}

void optor::dr4::Image::SetPos(::dr4::Vec2f pos)
{
    pos_ = pos;
}

::dr4::Vec2f optor::dr4::Image::GetPos() const
{
    return pos_;
}

void optor::dr4::Image::DrawOn(::dr4::Texture& texture) const
{
    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([&]() {
        sf::RenderStates states;
        states.transform.translate(pos_.x + myTexture.zero_.x,
                                   pos_.y + myTexture.zero_.y);
        myTexture.renderTexture_.draw(pixels_, states);
    });
}
