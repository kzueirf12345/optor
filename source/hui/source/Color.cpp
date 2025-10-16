#include <cassert>
#include <memory>

#include <SFML/Graphics/Color.hpp>

#include "hui/Color.hpp"
#include "hui/Vector.hpp"

class hui::ColorImpl : public sf::Color {
    public:
        ColorImpl()
        {}
        ColorImpl(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            :   sf::Color(red, green, blue, alpha)
        {}
        ColorImpl(uint32_t color) 
            :   sf::Color(color)
        {}
    private:
};

hui::Color::Color(const hui::Color& other) 
    : impl_(std::make_unique<hui::ColorImpl>(other.GetInt()))
{}
hui::Color& hui::Color::operator=(const hui::Color& other)
{
    hui::Color::SetInt(other.GetInt());
    return *this;
}

hui::Color::Color() 
    : impl_(std::make_unique<hui::ColorImpl>())
{}

hui::Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : impl_(std::make_unique<hui::ColorImpl>(red, green, blue, alpha))
{}

hui::Color::Color(const hui::Vector3d& normilizedColor, uint8_t alpha) 
    : hui::Color(
        normilizedColor.x * 255, 
        normilizedColor.y * 255, 
        normilizedColor.z * 255, 
        alpha
    )
{}

hui::Color::~Color() = default;

hui::Color::Color                (Color&& other) noexcept = default;
hui::Color& hui::Color::operator=(Color&& other) noexcept = default;

const void* hui::Color::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Color::GetImpl() noexcept {
    return impl_.get();
}

uint8_t  hui::Color::GetRed()   const noexcept {
    const auto* const impl = static_cast<const hui::ColorImpl*>(GetImpl());
    return impl->r;
}

uint8_t  hui::Color::GetGreen() const noexcept {
    const auto* const impl = static_cast<const hui::ColorImpl*>(GetImpl());
    return impl->g;
}

uint8_t  hui::Color::GetBlue()  const noexcept {
    const auto* const impl = static_cast<const hui::ColorImpl*>(GetImpl());
    return impl->b;
}

uint8_t  hui::Color::GetAlpha() const noexcept {
    const auto* const impl = static_cast<const hui::ColorImpl*>(GetImpl());
    return impl->a;
}

uint32_t hui::Color::GetInt()   const noexcept {
    const auto* const impl = static_cast<const hui::ColorImpl*>(GetImpl());
    return impl->toInteger();
}

hui::Vector3d hui::Color::GetNormalized() const noexcept {
    const auto* const impl = static_cast<const hui::ColorImpl*>(GetImpl());
    return hui::Vector3d(impl->r, impl->g, impl->b) / 255.;
}


void hui::Color::SetRed     (uint8_t  red)    noexcept {
    auto* const impl = static_cast<hui::ColorImpl*>(GetImpl());
    impl->r = red;
}

void hui::Color::SetGreen   (uint8_t  green)  noexcept {
    auto* const impl = static_cast<hui::ColorImpl*>(GetImpl());
    impl->g = green;
}

void hui::Color::SetBlue    (uint8_t  blue)   noexcept {
    auto* const impl = static_cast<hui::ColorImpl*>(GetImpl());
    impl->b = blue;
}

void hui::Color::SetAlpha   (uint8_t  alpha)  noexcept {
    auto* const impl = static_cast<hui::ColorImpl*>(GetImpl());
    impl->a = alpha;
}

static uint8_t GetColorPart_(uint32_t color, size_t num) noexcept {
    assert(num < 4);
    return (color >> (8 * (3 - num))) & 0xFF;
}

void hui::Color::SetInt     (uint32_t color)  noexcept {
    auto* const impl = static_cast<hui::ColorImpl*>(GetImpl());
    impl->r = GetColorPart_(color, 0);
    impl->g = GetColorPart_(color, 1);
    impl->b = GetColorPart_(color, 2);
    impl->a = GetColorPart_(color, 3);
}
