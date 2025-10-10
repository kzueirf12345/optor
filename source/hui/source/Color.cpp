#include <SFML/Graphics/Color.hpp>

#include "hui/Color.hpp"

class hui::ColorImpl : public sf::Color {
    public:
        ColorImpl(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            :   sf::Color(red, green, blue, alpha)
        {}
    private:
};

hui::Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : impl_(std::make_unique<hui::ColorImpl>(red, green, blue, alpha))
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