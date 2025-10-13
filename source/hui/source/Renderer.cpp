#include <memory>
#include <stdexcept>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "hui/Renderer.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Color.hpp"

class hui::RendererImpl: public sf::RenderTexture {
    public:
        RendererImpl(const hui::Vector2d& size)
            :   sf::RenderTexture()
        {
            if (!this->create(size.x, size.y)) {
                throw std::runtime_error("Can't create sf::RenderTexture");
            }
        }
    private:
};

hui::Renderer::Renderer(const hui::Vector2d& size)
    : impl_{std::make_unique<hui::RendererImpl>(size)}
{}

hui::Renderer::~Renderer() = default;

hui::Renderer::Renderer                (hui::Renderer&& other) noexcept = default;
hui::Renderer& hui::Renderer::operator=(hui::Renderer&& other) noexcept = default;

const void* hui::Renderer::GetImpl() const noexcept {
    return impl_.get();
}
void* hui::Renderer::GetImpl() noexcept {
    return impl_.get();
}

void hui::Renderer::Clear(const hui::Color& color) {
    auto* const impl = static_cast<hui::RendererImpl*>(GetImpl());
    ERROR_HANDLE(
        &hui::RendererImpl::clear, 
        impl, 
        sf::Color(color.GetInt())
    );
}
void hui::Renderer::Draw(const hui::Drawable& drawable) {
    auto* const impl = static_cast<hui::RendererImpl*>(GetImpl());
    ERROR_HANDLE([impl, &drawable](){
        impl->draw(*static_cast<const sf::Drawable*>(drawable.GetImpl()));
    });
}
void hui::Renderer::Display() {
    auto* const impl = static_cast<hui::RendererImpl*>(GetImpl());
    ERROR_HANDLE(&hui::RendererImpl::display, impl);
}

hui::Vector2d hui::Renderer::GetSize() const {
    const auto* const impl = static_cast<const hui::RendererImpl*>(GetImpl());
    const auto res = ERROR_HANDLE(&hui::RendererImpl::getSize, impl);
    return {static_cast<double>(res.x), static_cast<double>(res.y)};
}