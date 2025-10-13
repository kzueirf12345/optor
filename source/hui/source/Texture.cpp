#include "hui/Texture.hpp"
#include <SFML/Graphics/Texture.hpp>

class hui::TextureImpl: public sf::Texture {
    public:
        TextureImpl()
        {}
        TextureImpl(const hui::Vector2d& size)
        {
            if (!this->create(size.x, size.y)) {
                throw std::runtime_error("Can't create sf::Texture");
            }
        }
            
    private:
};

hui::Texture::Texture()
    :   impl_{std::make_unique<hui::TextureImpl>()}
{}

hui::Texture::Texture(const hui::Vector2d& size)
    :   impl_(std::make_unique<hui::TextureImpl>(size))
{}

hui::Texture::Texture                (hui::Texture&& other) noexcept = default;
hui::Texture& hui::Texture::operator=(hui::Texture&& other) noexcept = default;

hui::Texture::~Texture() = default;

const void* hui::Texture::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Texture::GetImpl() noexcept {
    return impl_.get();
}