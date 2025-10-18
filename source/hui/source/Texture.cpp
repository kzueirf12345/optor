#include <SFML/Graphics/Image.hpp>
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

// void hui::Texture::Update(const std::vector<uint32_t>& pixels) {
//     auto* const impl = static_cast<hui::TextureImpl*>(GetImpl());
    
//     // Преобразование в формат, ожидаемый SFML
//     std::vector<uint8_t> rgbaPixels(pixels.size() * 4);
//     for (size_t i = 0; i < pixels.size(); ++i) {
//         rgbaPixels[i * 4 + 3] = (pixels[i] >> 0) & 0xFF;  // R
//         rgbaPixels[i * 4 + 2] = (pixels[i] >> 8) & 0xFF;  // G
//         rgbaPixels[i * 4 + 1] = (pixels[i] >> 16) & 0xFF; // B
//         rgbaPixels[i * 4 + 0] = (pixels[i] >> 24) & 0xFF; // A
//     }
    
//     ERROR_HANDLE([impl, &rgbaPixels](){
//         impl->update(rgbaPixels.data());
//     });
// }

void hui::Texture::Update(const std::vector<uint32_t>& pixels) {
    auto* const impl = static_cast<hui::TextureImpl*>(GetImpl());
    ERROR_HANDLE([impl, &pixels](){
        impl->update(reinterpret_cast<const std::uint8_t*>(pixels.data()));
    });

    // const sf::Image img = impl->copyToImage();

    // for (size_t y = 0; y < img.getSize().y; ++y) {
    //     for (size_t x = 0; x < img.getSize().x; ++x) {
    //         if (img.getPixel(x, y).toInteger() != 255) std::cerr << "0x" << std::hex << img.getPixel(x, y).toInteger() << " ";
    //     }
    // }

    // for (size_t i = 0; i < impl->copyToImage().; ++i) {
    //     std::cerr << "0x" << std::hex <<  pixels[i] << " ";
    // }
}

/*!SECTION
    for (size_t i = 0; i < pixels.size(); ++i) {
        if (pixels[i] != 255) std::cerr << "0x" << std::hex <<  pixels[i] << " ";
        // exit(0);
    }
*/

void hui::Texture::SetImpl(void* impl) noexcept {
    assert(impl);

    impl_ = std::make_unique<hui::TextureImpl>(*static_cast<hui::TextureImpl*>(impl));
}