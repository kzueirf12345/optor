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

hui::Shape::Shape                (hui::Shape&& other) noexcept = default;
hui::Shape& hui::Shape::operator=(hui::Shape&& other) noexcept = default;


const void* hui::Shape::GetImpl() const noexcept {
    return impl_.get();
}


void* hui::Shape::GetImpl() noexcept {
    return impl_.get();
}


void hui::Shape::SetFillColor       (const hui::Color& color) {
    ERROR_HANDLE(&sf::Shape::setFillColor, *static_cast<hui::ShapeImpl*>(GetImpl()), *static_cast<const sf::Color*>(color.GetImpl()));
}

void hui::Shape::SetOutlineColor    (const hui::Color& color) {
    ERROR_HANDLE(&sf::Shape::setOutlineColor, *static_cast<hui::ShapeImpl*>(GetImpl()), *static_cast<const sf::Color*>(color.GetImpl()));
}

void hui::Shape::SetOutlineThickness(double thickness) {
    ERROR_HANDLE(&sf::Shape::setOutlineThickness, *static_cast<hui::ShapeImpl*>(GetImpl()), static_cast<float>(thickness));
}

void hui::Shape::SetPosition(const hui::Vector2d& position) {
    ERROR_HANDLE([&](){
        static_cast<hui::ShapeImpl*>(GetImpl())->setPosition(
            position.x, 
            position.y
        );}
    );
}

hui::Vector2d hui::Shape::GetPosition() const {
    const sf::Vector2f res = ERROR_HANDLE(
        &sf::Shape::getPosition, 
        *static_cast<const hui::ShapeImpl*>(GetImpl())
    );
    return {res.x, res.y};
}
