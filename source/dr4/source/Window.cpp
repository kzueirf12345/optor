#include <optional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "dr4/Window.hpp"
#include "dr4/Texture.hpp"

#include "common/ErrorHandler.hpp"
#include "dr4/event.hpp"
#include "dr4/texture.hpp"

void optor::dr4::Window::SetTitle(const std::string &title) 
{
    ERROR_HANDLE([this, &title](){
        title_ = title;
        window_.setTitle(title_);
    });
}

const std::string &optor::dr4::Window::GetTitle() const 
{
    return title_;
}

::dr4::Vec2f optor::dr4::Window::GetSize() const 
{
    const sf::Vector2u sizeSF = ERROR_HANDLE([this](){
        return window_.getSize();
    });

    return {static_cast<float>(sizeSF.x), static_cast<float>(sizeSF.y)};
}

void optor::dr4::Window::SetSize(const ::dr4::Vec2f& size)
{
    ERROR_HANDLE([this, &size](){
        size_ = {static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)};
        window_.setSize(size_);
    });
}

void optor::dr4::Window::Open() 
{
    ERROR_HANDLE([this](){
        window_.create(sf::VideoMode(size_.x, size_.y), title_);
    });
}

bool optor::dr4::Window::IsOpen() const 
{
    return ERROR_HANDLE([this](){
        return window_.isOpen();
    });
}

void optor::dr4::Window::Close() 
{
    ERROR_HANDLE([this](){
        window_.close();
    });
}

void optor::dr4::Window::Clear(const ::dr4::Color &color) 
{
    ERROR_HANDLE([this, &color](){
        window_.clear(sf::Color(color.r, color.g, color.b, color.a));
    });
}

void optor::dr4::Window::Draw(const ::dr4::Texture &texture, ::dr4::Vec2f pos) 
{
    const sf::Texture textureSF = ERROR_HANDLE([&texture](){
        return dynamic_cast<const optor::dr4::Texture&>(texture).renderTexture_.getTexture();
    });
    
     sf::Sprite spriteSF = ERROR_HANDLE([&textureSF](){
        return sf::Sprite(textureSF);
    });

    ERROR_HANDLE([&spriteSF, &pos](){
        spriteSF.setPosition(pos.x, pos.y);
    });

    ERROR_HANDLE([this, &spriteSF](){
        window_.draw(spriteSF);
    });
}

void optor::dr4::Window::Display() 
{
    ERROR_HANDLE([this](){
        window_.display();
    });
}

::dr4::Texture *optor::dr4::Window::CreateTexture() 
{
    return new optor::dr4::Texture();
}

std::optional<::dr4::Event> optor::dr4::Window::PollEvent() 
{
    sf::Event eventSF = {};

    if (!ERROR_HANDLE([this, &eventSF](){
            return window_.pollEvent(eventSF);
        })) {
        return std::nullopt;
    }

    ::dr4::Event event = {};

    switch(eventSF.type) {
        case sf::Event::EventType::MouseMoved: {
            event.type = ::dr4::Event::Type::MOUSE_MOVE;
            event.mouseMove = {.pos = {
                static_cast<float>(eventSF.mouseMove.x), 
                static_cast<float>(eventSF.mouseMove.y)
            }};
        }
        case sf::Event::EventType::MouseButtonPressed : {
            event.type = ::dr4::Event::Type::MOUSE_DOWN;
            event.mouseDown = {
                .pos = {
                    static_cast<float>(eventSF.mouseButton.x), 
                    static_cast<float>(eventSF.mouseButton.y)
                }
            };
            event.mouseDown.button = (int)eventSF.mouseButton.button;
            event.mouseDown.pressed = true;
        }
        case sf::Event::EventType::MouseButtonReleased : {
            event.type = ::dr4::Event::Type::MOUSE_UP;
            event.mouseUp = {
                .pos = {
                    static_cast<float>(eventSF.mouseButton.x), 
                    static_cast<float>(eventSF.mouseButton.y)
                }
            };
            event.mouseUp.button = (int)eventSF.mouseButton.button;
            event.mouseUp.pressed = true;
        }
        case sf::Event::EventType::MouseWheelScrolled : {
            event.type = ::dr4::Event::Type::MOUSE_WHEEL;
            // TODO
        }
        case sf::Event::EventType::KeyPressed : {
            event.type = ::dr4::Event::Type::KEY_DOWN;
            // TODO
        }
        case sf::Event::EventType::KeyReleased : {
            event.type = ::dr4::Event::Type::KEY_UP;
            // TODO
        }
        case sf::Event::EventType::Closed : {
            event.type = ::dr4::Event::Type::QUIT;
        }
        default:
            event.type = ::dr4::Event::Type::UNKNOWN;
    }

    return event;
}