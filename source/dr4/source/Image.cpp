#include <cassert>

#include "dr4/Image.hpp"

void optor::dr4::Image::SetPixel(unsigned x, unsigned y, ::dr4::Color color) {
    const size_t ind = 4 * (y * size_.x + x);

    pixels_[ind + 0] = color.r;
    pixels_[ind + 1] = color.g;
    pixels_[ind + 2] = color.b;
    pixels_[ind + 3] = color.a;
}
::dr4::Color optor::dr4::Image::GetPixel(unsigned x, unsigned y) const {
    const size_t ind = 4 * (y * size_.x + x);
    return {pixels_[ind], pixels_[ind + 1], pixels_[ind + 2], pixels_[ind + 3]};
}

void optor::dr4::Image::SetSize(::dr4::Vec2f size) {
    size_ = {static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)};

    pixels_.assign(size_.x * size_.y * 4, 0);
}

::dr4::Vec2f optor::dr4::Image::GetSize() const {
    return {static_cast<float>(size_.x), static_cast<float>(size_.y)};
}
float optor::dr4::Image::GetWidth() const {
    return size_.x;
}
float optor::dr4::Image::GetHeight() const {
    return size_.y;
}