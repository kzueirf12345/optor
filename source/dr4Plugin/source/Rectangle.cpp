#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "dr4Plugin/Rectangle.hpp"
#include "dr4Plugin/Texture.hpp"
#include "common/ErrorHandler.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"

optor::dr4::Rectangle::Rectangle()
    : rect_({1.0f, 1.0f})
{}

void optor::dr4::Rectangle::SetSize(::dr4::Vec2f size) {
    ERROR_HANDLE([this, &size](){
        rect_.setSize({size.x, size.y});
    });
}

void optor::dr4::Rectangle::SetFillColor(::dr4::Color color) {
    ERROR_HANDLE([this, &color](){
        rect_.setFillColor({color.r, color.g, color.b, color.a});
    });
}

void optor::dr4::Rectangle::SetBorderThickness(float thickness) {
    ERROR_HANDLE([this, thickness](){
        rect_.setOutlineThickness(thickness);
    });
}

void optor::dr4::Rectangle::SetBorderColor(::dr4::Color color) {
    ERROR_HANDLE([this, &color](){
        rect_.setOutlineColor({color.r, color.g, color.b, color.a});
    });
}

::dr4::Vec2f optor::dr4::Rectangle::GetSize() const {
    return ERROR_HANDLE([this](){
        sf::Vector2f sizeSF = rect_.getSize();
        return ::dr4::Vec2f{sizeSF.x, sizeSF.y};
    });
}

::dr4::Color optor::dr4::Rectangle::GetFillColor() const {
    return ERROR_HANDLE([this](){
        sf::Color colorSF = rect_.getFillColor();
        return ::dr4::Color{colorSF.r, colorSF.g, colorSF.b, colorSF.a};
    });
}

float optor::dr4::Rectangle::GetBorderThickness() const {
    return ERROR_HANDLE([this](){
        return rect_.getOutlineThickness();
    });
}

::dr4::Color optor::dr4::Rectangle::GetBorderColor() const {
    return ERROR_HANDLE([this](){
        sf::Color colorSF = rect_.getOutlineColor();
        return ::dr4::Color{colorSF.r, colorSF.g, colorSF.b, colorSF.a};
    });
}

void optor::dr4::Rectangle::DrawOn(::dr4::Texture& texture) const {
    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([this, &myTexture](){
        myTexture.renderTexture_.draw(
            rect_,
            sf::RenderStates().transform.translate(
                myTexture.zero_.x, 
                myTexture.zero_.y
            )
        );
    });
}

void optor::dr4::Rectangle::SetPos(::dr4::Vec2f pos) {
    ERROR_HANDLE([this, &pos](){
        rect_.setPosition({pos.x, pos.y});
    });
}

::dr4::Vec2f optor::dr4::Rectangle::GetPos() const {
    return ERROR_HANDLE([this](){
        sf::Vector2f posSF = rect_.getPosition();
        return ::dr4::Vec2f{posSF.x, posSF.y};
    });
}
