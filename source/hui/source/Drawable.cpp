#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp> 

#include "hui/Drawable.hpp"

class hui::DrawableImpl : public sf::Drawable {
    private:
    public:
        [[nodiscard]]       sf::Drawable* asSF()       noexcept {return this;}
        [[nodiscard]] const sf::Drawable* asSF() const noexcept {return this;}
};

hui::Drawable::~Drawable() = default;

template<typename T>
const T* hui::Drawable::GetImplAs() const noexcept {
    return static_cast<const T*>(impl_.get());
}

template<typename T>
T* hui::Drawable::GetImplAs() noexcept {
    return static_cast<T*>(impl_.get());
}

template const sf::Drawable* hui::Drawable::GetImplAs<const sf::Drawable>() const noexcept;
template       sf::Drawable* hui::Drawable::GetImplAs<      sf::Drawable>() noexcept;