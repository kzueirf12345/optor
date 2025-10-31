#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cassert>

#include "hui/Text.hpp"
#include "hui/Color.hpp"
#include "hui/Vector.hpp"
#include "hui/Font.hpp"
#include "common/ErrorHandler.hpp"

class hui::TextImpl : public sf::Text {
public:
    TextImpl() = default;

    explicit TextImpl(const std::string& string)
        : sf::Text(string, sf::Font(), 30)
    {}
};

hui::Text::Text()
    : impl_{std::make_unique<hui::TextImpl>()}
{}

hui::Text::Text(const std::string& string)
    : impl_{std::make_unique<hui::TextImpl>(string)}
{}

hui::Text::Text           (hui::Text&& other) noexcept = default;
hui::Text& hui::Text::operator=(hui::Text&& other) noexcept = default;

hui::Text::~Text() = default;

const void* hui::Text::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Text::GetImpl() noexcept {
    return impl_.get();
}

void hui::Text::SetImpl(void* impl) noexcept {
    assert(impl);
    impl_ = std::make_unique<hui::TextImpl>(*static_cast<hui::TextImpl*>(impl));
}

void hui::Text::SetString(const std::string& string) {
    auto* const impl = static_cast<hui::TextImpl*>(GetImpl());
    ERROR_HANDLE([impl, &string]() {
        impl->setString(string);
    });
}

void hui::Text::SetCharacterSize(unsigned int size) {
    auto* const impl = static_cast<hui::TextImpl*>(GetImpl());
    ERROR_HANDLE([impl, size]() {
        impl->setCharacterSize(size);
    });
}

void hui::Text::SetFillColor(const hui::Color& color) {
    auto* const impl = static_cast<hui::TextImpl*>(GetImpl());
    ERROR_HANDLE([impl, &color]() {
        impl->setFillColor(sf::Color(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha()));
    });
}

void hui::Text::SetFont(const hui::Font& font) {
    auto* const impl = static_cast<hui::TextImpl*>(GetImpl());
    ERROR_HANDLE([impl, &font]() {
        impl->setFont(*static_cast<const sf::Font*>(font.GetImpl()));
    });
}

void hui::Text::SetPosition(const hui::Vector2d& position) { //FIXME
    auto* const impl = static_cast<hui::TextImpl*>(GetImpl());
    ERROR_HANDLE([impl, &position]() {
        impl->setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
    });
}

hui::Vector2d hui::Text::GetPosition() const { //FIXME
    const auto* const impl = static_cast<const hui::TextImpl*>(GetImpl());
    const auto pos = impl->getPosition();
    return hui::Vector2d(pos.x, pos.y);
}

std::string hui::Text::GetString() const {
    const auto* const impl = static_cast<const hui::TextImpl*>(GetImpl());
    return impl->getString();
}

unsigned int hui::Text::GetCharacterSize() const {
    const auto* const impl = static_cast<const hui::TextImpl*>(GetImpl());
    return impl->getCharacterSize();
}

uint32_t hui::Text::GetFillColor() const {
    const auto* const impl = static_cast<const hui::TextImpl*>(GetImpl());
    const auto sfColor = impl->getFillColor();
    return sfColor.toInteger();
}

hui::Vector2d hui::Text::GetSize() const {
    const auto* const impl = static_cast<const hui::TextImpl*>(GetImpl());
    const sf::FloatRect bounds = impl->getLocalBounds();
    return hui::Vector2d(bounds.width, bounds.height);
}

