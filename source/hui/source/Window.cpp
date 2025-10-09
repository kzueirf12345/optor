#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "hui/Window.hpp"
#include "common/ErrorHandler.hpp"
#include "hui/Event.hpp"

class hui::WindowImpl : public sf::RenderWindow {
    private:
    public:
        WindowImpl(double width, double height, const std::string& title) 
            :   sf::RenderWindow {
                    sf::VideoMode(
                        static_cast<unsigned int>(width), 
                        static_cast<unsigned int>(height)
                    ), 
                    title
                }
        {}

};

hui::Window::Window(double width, double height, const std::string& title) 
    :   impl_{std::make_unique<hui::WindowImpl>(width, height, title)}
{}

hui::Window::Window                (hui::Window&& other) noexcept = default;
hui::Window& hui::Window::operator=(hui::Window&& other) noexcept = default;


hui::Window::~Window() = default;


void hui::Window::Clear() {
    ERROR_HANDLE([&](){ impl_->clear(); });
}

void hui::Window::Draw(const hui::Drawable& drawable) {
    ERROR_HANDLE(
        [&](const sf::Drawable* obj){
            impl_->draw(*obj);
        }, 
        drawable.GetImplAs<const sf::Drawable>()
    );
}

void hui::Window::Display() {
    ERROR_HANDLE([&](){ impl_->display(); });
}

bool hui::Window::isOpen() const {
    return ERROR_HANDLE([&](){ return impl_->isOpen(); });
}

void hui::Window::Close() {
    ERROR_HANDLE([&](){ impl_->close(); });
}

bool hui::Window::PoolEvent(hui::Event& event) {
    return ERROR_HANDLE(
        [&](sf::Event* obj){
            return impl_->pollEvent(*obj);
        }, 
        event.GetImplAs<sf::Event>()
    );
}
