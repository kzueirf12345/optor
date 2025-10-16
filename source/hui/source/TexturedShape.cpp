#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "hui/TexturedShape.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Sprite.hpp"

hui::TexturedShape::TexturedShape(const hui::Vector2d& boxSize) 
    :   hui::TexturedShape(boxSize, {0, 0})
{}

hui::TexturedShape::TexturedShape(const hui::Vector2d& boxSize, const hui::Vector2d& position)
    :   boxSize_{boxSize}, 
        texture_{ERROR_HANDLE([this](){
            return hui::Texture(boxSize_);
        })},
        pixelBuffer_(boxSize_.x * boxSize_.y),
        sprite_{}
{
    ERROR_HANDLE([this](){
        sprite_.SetTexture(texture_);
    });

    ERROR_HANDLE([this, &position](){ // FIXME
        SetPosition(position);
    });
}


hui::TexturedShape::~TexturedShape() = default;

const void* hui::TexturedShape::GetImpl() const noexcept {
    return sprite_.GetImpl();
}
void* hui::TexturedShape::GetImpl() noexcept {
    return sprite_.GetImpl();
}

void hui::TexturedShape::Update() {
    ERROR_HANDLE([this](){
        texture_.Update(pixelBuffer_);
    });
}

void hui::TexturedShape::SetPosition(const hui::Vector2d& position) { // FIXME
    ERROR_HANDLE([this, &position](){
        sprite_.SetPosition(
            {position.x, position.y}
        );}
    );
}

hui::Vector2d hui::TexturedShape::GetPosition() const { // FIXME
    return ERROR_HANDLE(
        &hui::Sprite::GetPosition, 
        sprite_
    );
}
