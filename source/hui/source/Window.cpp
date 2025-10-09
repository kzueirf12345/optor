#include <SFML/Graphics/RenderStates.hpp>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

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
    ERROR_HANDLE(&sf::RenderWindow::clear, impl_, sf::Color(0, 0, 0, 255));
}

void hui::Window::Draw(const hui::Drawable& drawable) {
    ERROR_HANDLE([&](){
        impl_->draw(*static_cast<const sf::Drawable*>(drawable.GetImplAs()));
    });
}

void hui::Window::Display() {
    ERROR_HANDLE(&sf::RenderWindow::display, *impl_.get());
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
        static_cast<sf::Event*>(event.GetImplAs())
    );
}
