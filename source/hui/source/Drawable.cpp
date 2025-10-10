#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp> 
#include <memory>

#include "hui/Drawable.hpp"

class hui::DrawableImpl : public sf::Drawable {
    public:
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            throw std::logic_error("not override method");
        }
    private:
};

hui::Drawable::Drawable(): impl_(std::make_unique<hui::DrawableImpl>()) {}

hui::Drawable::~Drawable() = default;

hui::Drawable::Drawable                (hui::Drawable&& other) noexcept = default;
hui::Drawable& hui::Drawable::operator=(hui::Drawable&& other) noexcept = default;

const void* hui::Drawable::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Drawable::GetImpl() noexcept {
    return impl_.get();
}

// template const sf::Drawable* hui::Drawable::GetImplAs<const sf::Drawable>() const noexcept;
// template       sf::Drawable* hui::Drawable::GetImplAs<      sf::Drawable>()       noexcept;