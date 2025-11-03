#include <cassert>
#include <cstdint>
#include <stdexcept>

#include "dr4/Image.hpp"
#include "dr4/texture.hpp"

#include "common/ErrorHandler.hpp"

void optor::dr4::Image::Create(::dr4::Vec2f size, ::dr4::Image::ColorMode mode, ::dr4::Color color) 
{
    assert(size.x > 0);
    assert(size.y > 0);

    size_ = {static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)};
    mode_ = mode;

    pixels_.assign(size_.x * size_.y * 4, 0);

    if (color == ::dr4::Color(0, 0, 0, 0)) {
        return;
    }

    for (size_t y = 0; y < size_.y; ++y) {
        for (size_t x = 0; x < size_.x; ++x) {
            ERROR_HANDLE([this, &color, x, y](){
                SetPixel(x, y, color);
            });
        }
    }
}

::dr4::Vec2f optor::dr4::Image::GetSize() const 
{
    return {static_cast<float>(size_.x), static_cast<float>(size_.y)};
}

void optor::dr4::Image::SetPixel(size_t x, size_t y, ::dr4::Color color) 
{
    const size_t ind = 4 * (y * size_.x + x);

    switch (mode_) {
        case ::dr4::Image::ColorMode::RGBA:
            pixels_[ind + 0] = color.r;
            pixels_[ind + 1] = color.g;
            pixels_[ind + 2] = color.b;
            pixels_[ind + 3] = color.a;
            break;
        case ::dr4::Image::ColorMode::ABGR:
            pixels_[ind + 0] = color.a;
            pixels_[ind + 1] = color.b;
            pixels_[ind + 2] = color.g;
            pixels_[ind + 3] = color.r;
            break;
        default:
            throw std::overflow_error("Unknown color mode enum");
    }
}
::dr4::Color optor::dr4::Image::GetPixel(size_t x, size_t y) const 
{
    const size_t ind = 4 * (y * size_.x + x);
    return {pixels_[ind], pixels_[ind + 1], pixels_[ind + 2], pixels_[ind + 3]};
}

const uint8_t* optor::dr4::Image::GetArray() const
{
    return pixels_.begin().base();
}