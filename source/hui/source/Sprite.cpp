#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "hui/Sprite.hpp"
#include "hui/Texture.hpp"
#include "common/ErrorHandler.hpp"

class hui::SpriteImpl: public sf::Sprite {
    public:    
        SpriteImpl(){}
        SpriteImpl(const hui::Texture& texture)
            :   sf::Sprite(*static_cast<const sf::Texture*>(texture.GetImpl())) 
        {}
    private:
};

hui::Sprite::Sprite()
    :   impl_{std::make_unique<hui::SpriteImpl>()}
{}

hui::Sprite::Sprite(const hui::Texture& texture)
    :   impl_{std::make_unique<hui::SpriteImpl>(texture)}
{}

hui::Sprite::Sprite                (hui::Sprite&& other) noexcept = default;
hui::Sprite& hui::Sprite::operator=(hui::Sprite&& other) noexcept = default;

hui::Sprite::~Sprite() = default;

const void* hui::Sprite::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Sprite::GetImpl() noexcept {
    return impl_.get();
}

void hui::Sprite::SetTexture(const hui::Texture& texture) {
          auto* const         impl = static_cast<hui::SpriteImpl*>(GetImpl());
    const auto* const texture_impl = static_cast<const sf::Texture*>(texture.GetImpl());
    ERROR_HANDLE([impl, texture_impl](){
        impl->setTexture(*texture_impl);
    });
}