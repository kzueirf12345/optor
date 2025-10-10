#include <SFML/System/Vector2.hpp>
#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "hui/RectangleShape.hpp"
#include "common/ErrorHandler.hpp"

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

hui::RectangleShape::RectangleShape                (hui::RectangleShape&& other) noexcept = default;
hui::RectangleShape& hui::RectangleShape::operator=(hui::RectangleShape&& other) noexcept = default;

const void* hui::RectangleShape::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::RectangleShape::GetImpl() noexcept {
    return impl_.get();
}

const hui::Vector2d hui::RectangleShape::GetSize() const {
    auto res = ERROR_HANDLE(
        &sf::RectangleShape::getSize, 
        *static_cast<const hui::RectangleShapeImpl*>(GetImpl())
    );
    return {res.x, res.y};
}