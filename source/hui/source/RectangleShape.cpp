#include <SFML/System/Vector2.hpp>
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "hui/RectangleShape.hpp"

class hui::RectangleShapeImpl: public sf::RectangleShape {
    public:
        RectangleShapeImpl(const hui::Vector2d& size) 
            :   sf::RectangleShape(sf::Vector2f(size.x, size.y)) 
        {}

    private:
};

hui::RectangleShape::RectangleShape(const hui::Vector2d& size) 
    :   impl_{std::make_unique<hui::RectangleShapeImpl>(size)}
{}

hui::RectangleShape::~RectangleShape() = default;


const void* hui::RectangleShape::GetImplAs() const noexcept {
    return impl_.get();
}

void* hui::RectangleShape::GetImplAs() noexcept {
    return impl_.get();
}

// template const sf::RectangleShape* hui::RectangleShape::GetImplAs<const sf::RectangleShape>() const noexcept;
// template       sf::RectangleShape* hui::RectangleShape::GetImplAs<      sf::RectangleShape>() noexcept;