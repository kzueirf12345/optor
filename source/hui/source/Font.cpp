#include <SFML/Graphics/Font.hpp>
#include <cassert>
#include <memory>

#include "hui/Font.hpp"
#include "common/ErrorHandler.hpp"

class hui::FontImpl : public sf::Font {
public:
    FontImpl() = default;
    explicit FontImpl(const std::string& filename) {
        if (!this->loadFromFile(filename)) {
            throw std::runtime_error("Can't load font from file: " + filename);
        }
    }
};

hui::Font::Font()
    : impl_{std::make_unique<hui::FontImpl>()}
{}

hui::Font::Font(const std::string& filename)
    : impl_{std::make_unique<hui::FontImpl>(filename)}
{}

hui::Font::Font                (hui::Font&& other) noexcept = default;
hui::Font& hui::Font::operator=(hui::Font&& other) noexcept = default;

hui::Font::~Font() = default;

const void* hui::Font::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Font::GetImpl() noexcept {
    return impl_.get();
}

void hui::Font::SetImpl(void* impl) noexcept {
    assert(impl);
    impl_ = std::make_unique<hui::FontImpl>(*static_cast<hui::FontImpl*>(impl));
}

bool hui::Font::LoadFromFile(const std::string& filename) {
    auto* const impl = static_cast<hui::FontImpl*>(GetImpl());
    bool result = false;
    ERROR_HANDLE([impl, &filename, &result]() {
        result = impl->loadFromFile(filename);
    });
    return result;
}
