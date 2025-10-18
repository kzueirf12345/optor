#include "hui/Color.hpp"
#include <algorithm>

namespace hui 
{

Color::Color() : red_(0), green_(0), blue_(0), alpha_(255) {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) 
    : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

Color::Color(const hui::Vector3d& normalizedColor, uint8_t alpha)
    : alpha_(alpha)
{
    red_ = static_cast<uint8_t>(normalizedColor.x * 255);
    green_ = static_cast<uint8_t>(normalizedColor.y * 255);
    blue_ = static_cast<uint8_t>(normalizedColor.z * 255);
}

Color::~Color() = default;

Color::Color(const Color& other) = default;

Color& Color::operator=(const Color& other) = default;

Color::Color(Color&& other) noexcept = default;

Color& Color::operator=(Color&& other) noexcept = default;

uint8_t Color::GetRed() const noexcept { return red_; }

uint8_t Color::GetGreen() const noexcept { return green_; }

uint8_t Color::GetBlue() const noexcept { return blue_; }

uint8_t Color::GetAlpha() const noexcept { return alpha_; }

uint32_t Color::GetInt() const noexcept {
    return (static_cast<uint32_t>(red_) << 24) |
           (static_cast<uint32_t>(green_) << 16) |
           (static_cast<uint32_t>(blue_) << 8) |
           static_cast<uint32_t>(alpha_);
}

uint32_t Color::GetABGR() const noexcept {
    return (static_cast<uint32_t>(alpha_) << 24) |
           (static_cast<uint32_t>(blue_) << 16) |
           (static_cast<uint32_t>(green_) << 8) |
           static_cast<uint32_t>(red_);
}

hui::Vector3d Color::GetNormalized() const noexcept {
    return hui::Vector3d(
        static_cast<double>(red_) / 255.0,
        static_cast<double>(green_) / 255.0,
        static_cast<double>(blue_) / 255.0
    );
}

void Color::SetRed(uint8_t red) noexcept { red_ = red; }

void Color::SetGreen(uint8_t green) noexcept { green_ = green; }

void Color::SetBlue(uint8_t blue) noexcept { blue_ = blue; }

void Color::SetAlpha(uint8_t alpha) noexcept { alpha_ = alpha; }

void Color::SetInt(uint32_t color) noexcept {
    red_ = static_cast<uint8_t>((color >> 24) & 0xFF);
    green_ = static_cast<uint8_t>((color >> 16) & 0xFF);
    blue_ = static_cast<uint8_t>((color >> 8) & 0xFF);
    alpha_ = static_cast<uint8_t>(color & 0xFF);
}

bool Color::operator==(const Color& other) const noexcept {
    return red_ == other.red_ && 
           green_ == other.green_ && 
           blue_ == other.blue_ && 
           alpha_ == other.alpha_;
}

bool Color::operator!=(const Color& other) const noexcept {
    return !(*this == other);
}

Color Color::operator+(const Color& other) const noexcept {
    return Color(
        static_cast<uint8_t>(std::min(255, int(red_) + int(other.red_))),
        static_cast<uint8_t>(std::min(255, int(green_) + int(other.green_))),
        static_cast<uint8_t>(std::min(255, int(blue_) + int(other.blue_))),
        static_cast<uint8_t>(std::min(255, int(alpha_) + int(other.alpha_)))
    );
}

Color Color::operator-(const Color& other) const noexcept {
    return Color(
        static_cast<uint8_t>(std::max(0, int(red_) - int(other.red_))),
        static_cast<uint8_t>(std::max(0, int(green_) - int(other.green_))),
        static_cast<uint8_t>(std::max(0, int(blue_) - int(other.blue_))),
        static_cast<uint8_t>(std::max(0, int(alpha_) - int(other.alpha_)))
    );
}

Color Color::operator*(float scalar) const noexcept {
    return Color(
        static_cast<uint8_t>(std::min(255.0f, red_ * scalar)),
        static_cast<uint8_t>(std::min(255.0f, green_ * scalar)),
        static_cast<uint8_t>(std::min(255.0f, blue_ * scalar)),
        static_cast<uint8_t>(std::min(255.0f, alpha_ * scalar))
    );
}

Color Color::operator/(float scalar) const noexcept {
    if (scalar == 0.0f) return *this;
    return Color(
        static_cast<uint8_t>(std::max(0.0f, red_ / scalar)),
        static_cast<uint8_t>(std::max(0.0f, green_ / scalar)),
        static_cast<uint8_t>(std::max(0.0f, blue_ / scalar)),
        static_cast<uint8_t>(std::max(0.0f, alpha_ / scalar))
    );
}

Color& Color::operator+=(const Color& other) noexcept {
    *this = *this + other;
    return *this;
}

Color& Color::operator-=(const Color& other) noexcept {
    *this = *this - other;
    return *this;
}

Color& Color::operator*=(float scalar) noexcept {
    *this = *this * scalar;
    return *this;
}

Color& Color::operator/=(float scalar) noexcept {
    *this = *this / scalar;
    return *this;
}

Color Color::Blend(const Color& other) const noexcept {
    if (alpha_ == 0) return other;
    if (other.alpha_ == 0) return *this;
    
    double alpha1 = alpha_ / 255.0;
    double alpha2 = other.alpha_ / 255.0;
    double alpha = alpha1 + alpha2 * (1.0 - alpha1);
    
    return Color(
        static_cast<uint8_t>((red_ * alpha1 + other.red_ * alpha2 * (1.0 - alpha1)) / alpha),
        static_cast<uint8_t>((green_ * alpha1 + other.green_ * alpha2 * (1.0 - alpha1)) / alpha),
        static_cast<uint8_t>((blue_ * alpha1 + other.blue_ * alpha2 * (1.0 - alpha1)) / alpha),
        static_cast<uint8_t>(alpha * 255)
    );
}

Color operator*(float scalar, const Color& color) noexcept {
    return color * scalar;
}

} // namespace hui