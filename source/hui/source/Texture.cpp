#include <memory>
#include <cassert>

#include <SFML/Graphics/Texture.hpp>

#include "hui/Texture.hpp"
#include "common/ErrorHandler.hpp"

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
        TextureImpl(const TextureImpl& other) = default;
            
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

void hui::Texture::Update(const std::vector<uint32_t>& pixels) {
    auto* const impl = static_cast<hui::TextureImpl*>(GetImpl());
    ERROR_HANDLE([impl, &pixels](){
        impl->update(reinterpret_cast<const std::uint8_t*>(pixels.data()));
    });
}

void hui::Texture::SetImpl(void* impl) noexcept {
    assert(impl);

    impl_ = std::make_unique<hui::TextureImpl>(*static_cast<hui::TextureImpl*>(impl));
}