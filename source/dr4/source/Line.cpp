#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "dr4/Line.hpp"
#include "dr4/Texture.hpp"

#include "common/ErrorHandler.hpp"


optor::dr4::Line::Line() 
    :   vertices_(sf::Quads, 4),
        start_{},
        end_{},
        pos_{},
        thickness_(1.0f),
        offset_{}
{
    UpdateOffset();
    UpdateVertices();
}

void optor::dr4::Line::SetStart(::dr4::Vec2f start) {
    start_ = start;
    UpdateOffset();
    UpdateVertices();
}

void optor::dr4::Line::SetEnd(::dr4::Vec2f end) {
    end_ = end;
    UpdateOffset();
    UpdateVertices();
}

void optor::dr4::Line::SetColor(::dr4::Color color) {
    const sf::Color sfColor(color.r, color.g, color.b, color.a);
    for (int i = 0; i < 4; ++i) {
        vertices_[i].color = sfColor;
    }
}

void optor::dr4::Line::SetThickness(float thickness) {
    thickness_ = thickness;
    UpdateOffset();
    UpdateVertices();
}

::dr4::Vec2f optor::dr4::Line::GetStart() const {
    return start_;
}

::dr4::Vec2f optor::dr4::Line::GetEnd() const {
    return end_;
}

::dr4::Color optor::dr4::Line::GetColor() const {
    const sf::Color colorSF = vertices_[0].color;
    return {colorSF.r, colorSF.g, colorSF.b, colorSF.a};
}

float optor::dr4::Line::GetThickness() const {
    return thickness_;
}

void optor::dr4::Line::DrawOn(::dr4::Texture& texture) const {
    optor::dr4::Texture& myTexture = dynamic_cast<optor::dr4::Texture&>(texture);

    ERROR_HANDLE([this, &myTexture](){
        myTexture.renderTexture_.draw(
            vertices_,
            sf::RenderStates().transform.translate(
                pos_.x + offset_.x + myTexture.zero_.x, 
                pos_.y + offset_.y + myTexture.zero_.y
            )
        );
    });
}

void optor::dr4::Line::SetPos(::dr4::Vec2f pos) {
    pos_ = pos;
}

::dr4::Vec2f optor::dr4::Line::GetPos() const {
    return pos_;
}

void optor::dr4::Line::UpdateOffset() {
    ERROR_HANDLE([this](){
        ::dr4::Vec2f direction = {end_.x - start_.x, end_.y - start_.y};
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        ::dr4::Vec2f unitDirection = {direction.x / length, direction.y / length};
        ::dr4::Vec2f unitPerpendicular = {-unitDirection.y, unitDirection.x};
        
        offset_ = {
            unitPerpendicular.x * (thickness_ / 2.0f),
            unitPerpendicular.y * (thickness_ / 2.0f)
        };
    });
}

void optor::dr4::Line::UpdateVertices() {
    ERROR_HANDLE([this](){
        vertices_[0].position = sf::Vector2f(
            start_.x, 
            start_.y
        );
        vertices_[1].position = sf::Vector2f(
            end_.x, 
            end_.y
        );
        vertices_[2].position = sf::Vector2f(
            end_.x, 
            end_.y
        );
        vertices_[3].position = sf::Vector2f(
            start_.x, 
            start_.y
        );
    });
}