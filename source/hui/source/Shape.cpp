#include <SFML/Graphics/Color.hpp>
#include <memory>

#include <SFML/Graphics/Shape.hpp>
#include <stdexcept>

#include "hui/Shape.hpp"
#include "common/ErrorHandler.hpp"

class hui::ShapeImpl: public sf::Shape {
    public:
        virtual std::size_t getPointCount() const override {
            throw std::logic_error("not override method");
        }
        
        virtual sf::Vector2f getPoint(std::size_t index) const override {
            throw std::logic_error("not override method");
        }

    protected:
    private:
};

hui::Shape::Shape() : impl_(std::make_unique<hui::ShapeImpl>()) {}

hui::Shape::~Shape() = default;


const void* hui::Shape::GetImplAs() const noexcept {
    return impl_.get();
}


void* hui::Shape::GetImplAs() noexcept {
    return impl_.get();
}

// template const sf::Shape* hui::Shape::GetImplAs<const sf::Shape>() const noexcept;
// template       sf::Shape* hui::Shape::GetImplAs<      sf::Shape>()       noexcept;


void hui::Shape::SetFillColor       (const hui::Color& color) {
    ERROR_HANDLE(&sf::Shape::setFillColor, *static_cast<hui::ShapeImpl*>(GetImplAs()), *static_cast<const sf::Color*>(color.GetImplAs()));
}

void hui::Shape::SetOutlineColor    (const hui::Color& color) {
    ERROR_HANDLE(&sf::Shape::setOutlineColor, *static_cast<hui::ShapeImpl*>(GetImplAs()), *static_cast<const sf::Color*>(color.GetImplAs()));
}

void hui::Shape::SetOutlineThickness(double thickness) {
    ERROR_HANDLE(&sf::Shape::setOutlineThickness, *static_cast<hui::ShapeImpl*>(GetImplAs()), static_cast<float>(thickness));
}
