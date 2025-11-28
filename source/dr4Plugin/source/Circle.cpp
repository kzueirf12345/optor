#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "dr4Plugin/Circle.hpp"
#include "dr4Plugin/Texture.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/math/vec2.hpp"

optor::dr4::Circle::Circle()
    :   circle_(1)
{}
    
void optor::dr4::Circle::SetCenter(::dr4::Vec2f center) {
    ERROR_HANDLE([this, &center](){
        SetPos(center - ::dr4::Vec2f(circle_.getRadius(), circle_.getRadius()));
    });
}

void optor::dr4::Circle::SetRadius(::dr4::Vec2f radius) {
    ERROR_HANDLE([this, radius](){
        circle_.setRadius(radius.x);
        circle_.setScale(1, radius.y / radius.x);
    });
}

void optor::dr4::Circle::SetFillColor(::dr4::Color color) {
    ERROR_HANDLE([this, &color](){
        circle_.setFillColor({color.r, color.g, color.b, color.a});
    });
}

void optor::dr4::Circle::SetBorderColor(::dr4::Color color) {
    ERROR_HANDLE([this, &color](){
        circle_.setOutlineColor({color.r, color.g, color.b, color.a});
    });
}

void optor::dr4::Circle::SetBorderThickness(float thickness) {
    ERROR_HANDLE([this, thickness](){
        circle_.setOutlineThickness(thickness);
    });
}

::dr4::Vec2f optor::dr4::Circle::GetCenter() const {
    return ERROR_HANDLE([this](){
        return GetPos() + ::dr4::Vec2f{circle_.getRadius(), circle_.getRadius()};
    });
}

::dr4::Vec2f optor::dr4::Circle::GetRadius() const {
    return ERROR_HANDLE([this](){
        const float radius = circle_.getRadius();
        const sf::Vector2f scale = circle_.getScale();
        return ::dr4::Vec2f(radius * scale.x, radius * scale.y);
    });
}

::dr4::Color optor::dr4::Circle::GetFillColor() const {
    return ERROR_HANDLE([this](){
        sf::Color colorSF = circle_.getFillColor();
        return ::dr4::Color{colorSF.r, colorSF.g, colorSF.b, colorSF.a};
    });
}

::dr4::Color optor::dr4::Circle::GetBorderColor() const {
    return ERROR_HANDLE([this](){
        sf::Color colorSF = circle_.getOutlineColor();
        return ::dr4::Color{colorSF.r, colorSF.g, colorSF.b, colorSF.a};
    });
}

float optor::dr4::Circle::GetBorderThickness() const {
    return ERROR_HANDLE([this](){
        return circle_.getOutlineThickness();
    });
}

void optor::dr4::Circle::DrawOn(::dr4::Texture& texture) const {
    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([this, &myTexture](){
        myTexture.renderTexture_.draw(
            circle_,
            sf::RenderStates().transform.translate(
                myTexture.zero_.x, 
                myTexture.zero_.y
            )
        );
    });
}

void optor::dr4::Circle::SetPos(::dr4::Vec2f pos) {
    ERROR_HANDLE([this, &pos](){
        circle_.setPosition({pos.x, pos.y});
    });
}

::dr4::Vec2f optor::dr4::Circle::GetPos() const {
    return ERROR_HANDLE([this](){
        sf::Vector2f posSF = circle_.getPosition();
        return ::dr4::Vec2f{posSF.x, posSF.y};
    });
}
