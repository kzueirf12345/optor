#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <stdexcept>

#include "hui/Event.hpp"

class hui::EventImpl: public sf::Event {
    public:
        EventImpl() : sf::Event() {}
    private:
};

hui::Event::Event() 
    : impl_(std::make_unique<hui::EventImpl>()) 
{}

hui::Event::~Event() = default;

const void* hui::Event::GetImpl() const noexcept {
    return impl_.get();
}

void* hui::Event::GetImpl() noexcept {
    return impl_.get();
}

#define CASE_RET_TYPE_(guiType, huiType) \
        case guiType: return huiType

hui::Event::Type hui::Event::GetType() const {
    switch (static_cast<const hui::EventImpl*>(GetImpl())->type) {
        CASE_RET_TYPE_(sf::Event::EventType::Closed,                hui::Event::Type::Closed);
        CASE_RET_TYPE_(sf::Event::EventType::Resized,               hui::Event::Type::Resized);
        CASE_RET_TYPE_(sf::Event::EventType::LostFocus,             hui::Event::Type::LostFocus);
        CASE_RET_TYPE_(sf::Event::EventType::GainedFocus,           hui::Event::Type::GainedFocus);
        CASE_RET_TYPE_(sf::Event::EventType::TextEntered,           hui::Event::Type::TextEntered);
        CASE_RET_TYPE_(sf::Event::EventType::KeyPressed,            hui::Event::Type::KeyPressed);
        CASE_RET_TYPE_(sf::Event::EventType::KeyReleased,           hui::Event::Type::KeyReleased);
        CASE_RET_TYPE_(sf::Event::EventType::MouseWheelMoved,       hui::Event::Type::MouseWheelMoved);
        CASE_RET_TYPE_(sf::Event::EventType::MouseWheelScrolled,    hui::Event::Type::MouseWheelScrolled);
        CASE_RET_TYPE_(sf::Event::EventType::MouseButtonPressed,    hui::Event::Type::MouseButtonPressed);
        CASE_RET_TYPE_(sf::Event::EventType::MouseButtonReleased,   hui::Event::Type::MouseButtonReleased);
        CASE_RET_TYPE_(sf::Event::EventType::MouseMoved,            hui::Event::Type::MouseMoved);
        CASE_RET_TYPE_(sf::Event::EventType::MouseEntered,          hui::Event::Type::MouseEntered);
        CASE_RET_TYPE_(sf::Event::EventType::MouseLeft,             hui::Event::Type::MouseLeft);
        CASE_RET_TYPE_(sf::Event::EventType::JoystickButtonPressed, hui::Event::Type::JoystickButtonPressed);
        CASE_RET_TYPE_(sf::Event::EventType::JoystickButtonReleased,hui::Event::Type::JoystickButtonReleased);
        CASE_RET_TYPE_(sf::Event::EventType::JoystickMoved,         hui::Event::Type::JoystickMoved);
        CASE_RET_TYPE_(sf::Event::EventType::JoystickConnected,     hui::Event::Type::JoystickConnected);
        CASE_RET_TYPE_(sf::Event::EventType::JoystickDisconnected,  hui::Event::Type::JoystickDisconnected);
        CASE_RET_TYPE_(sf::Event::EventType::TouchBegan,            hui::Event::Type::TouchBegan);
        CASE_RET_TYPE_(sf::Event::EventType::TouchMoved,            hui::Event::Type::TouchMoved);
        CASE_RET_TYPE_(sf::Event::EventType::TouchEnded,            hui::Event::Type::TouchEnded);
        CASE_RET_TYPE_(sf::Event::EventType::SensorChanged,         hui::Event::Type::SensorChanged);
        CASE_RET_TYPE_(sf::Event::EventType::Count,                 hui::Event::Type::Count);
        default:
            throw std::overflow_error("Unknown Event type");
    }
    throw std::overflow_error("Unknown Event type");
}

hui::Event::MouseButton hui::Event::GetMouseButton() const {
    switch (static_cast<const hui::EventImpl*>(GetImpl())->mouseButton.button) {
        CASE_RET_TYPE_(sf::Mouse::Button::Left,         hui::Event::MouseButton::Left);
        CASE_RET_TYPE_(sf::Mouse::Button::Right,        hui::Event::MouseButton::Right);
        CASE_RET_TYPE_(sf::Mouse::Button::Middle,       hui::Event::MouseButton::Middle);
        CASE_RET_TYPE_(sf::Mouse::Button::XButton1,     hui::Event::MouseButton::XButton1);    
        CASE_RET_TYPE_(sf::Mouse::Button::XButton2,     hui::Event::MouseButton::XButton2);    
        CASE_RET_TYPE_(sf::Mouse::Button::ButtonCount,  hui::Event::MouseButton::ButtonCount);    
        default:
            throw std::overflow_error("Unknown MouseButton type");
    }
    throw std::overflow_error("Unknown MouseButton type");
}

hui::Event::MouseWheel hui::Event::GetMouseWheel() const {
    switch (static_cast<const hui::EventImpl*>(GetImpl())->mouseWheelScroll.wheel) {
        CASE_RET_TYPE_(sf::Mouse::Wheel::VerticalWheel,   hui::Event::MouseWheel::VerticalWheel);
        CASE_RET_TYPE_(sf::Mouse::Wheel::HorizontalWheel, hui::Event::MouseWheel::HorizontalWheel);
        default:
            throw std::overflow_error("Unknown MouseWheel type");
    }
    throw std::overflow_error("Unknown MouseWheel type");
}

hui::Event::KeyboardButton  hui::Event::GetKeyboardButton() const {
    switch (static_cast<const hui::EventImpl*>(GetImpl())->key.code) {
        CASE_RET_TYPE_(sf::Keyboard::Key::Unknown,     hui::Event::KeyboardButton::Unknown);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::A,           hui::Event::KeyboardButton::A);           
        CASE_RET_TYPE_(sf::Keyboard::Key::B,           hui::Event::KeyboardButton::B);           
        CASE_RET_TYPE_(sf::Keyboard::Key::C,           hui::Event::KeyboardButton::C);           
        CASE_RET_TYPE_(sf::Keyboard::Key::D,           hui::Event::KeyboardButton::D);           
        CASE_RET_TYPE_(sf::Keyboard::Key::E,           hui::Event::KeyboardButton::E);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F,           hui::Event::KeyboardButton::F);           
        CASE_RET_TYPE_(sf::Keyboard::Key::G,           hui::Event::KeyboardButton::G);           
        CASE_RET_TYPE_(sf::Keyboard::Key::H,           hui::Event::KeyboardButton::H);           
        CASE_RET_TYPE_(sf::Keyboard::Key::I,           hui::Event::KeyboardButton::I);           
        CASE_RET_TYPE_(sf::Keyboard::Key::J,           hui::Event::KeyboardButton::J);           
        CASE_RET_TYPE_(sf::Keyboard::Key::K,           hui::Event::KeyboardButton::K);           
        CASE_RET_TYPE_(sf::Keyboard::Key::L,           hui::Event::KeyboardButton::L);           
        CASE_RET_TYPE_(sf::Keyboard::Key::M,           hui::Event::KeyboardButton::M);           
        CASE_RET_TYPE_(sf::Keyboard::Key::N,           hui::Event::KeyboardButton::N);           
        CASE_RET_TYPE_(sf::Keyboard::Key::O,           hui::Event::KeyboardButton::O);           
        CASE_RET_TYPE_(sf::Keyboard::Key::P,           hui::Event::KeyboardButton::P);           
        CASE_RET_TYPE_(sf::Keyboard::Key::Q,           hui::Event::KeyboardButton::Q);           
        CASE_RET_TYPE_(sf::Keyboard::Key::R,           hui::Event::KeyboardButton::R);           
        CASE_RET_TYPE_(sf::Keyboard::Key::S,           hui::Event::KeyboardButton::S);           
        CASE_RET_TYPE_(sf::Keyboard::Key::T,           hui::Event::KeyboardButton::T);           
        CASE_RET_TYPE_(sf::Keyboard::Key::U,           hui::Event::KeyboardButton::U);           
        CASE_RET_TYPE_(sf::Keyboard::Key::V,           hui::Event::KeyboardButton::V);           
        CASE_RET_TYPE_(sf::Keyboard::Key::W,           hui::Event::KeyboardButton::W);           
        CASE_RET_TYPE_(sf::Keyboard::Key::X,           hui::Event::KeyboardButton::X);           
        CASE_RET_TYPE_(sf::Keyboard::Key::Y,           hui::Event::KeyboardButton::Y);           
        CASE_RET_TYPE_(sf::Keyboard::Key::Z,           hui::Event::KeyboardButton::Z);           
        CASE_RET_TYPE_(sf::Keyboard::Key::Num0,        hui::Event::KeyboardButton::Num0);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num1,        hui::Event::KeyboardButton::Num1);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num2,        hui::Event::KeyboardButton::Num2);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num3,        hui::Event::KeyboardButton::Num3);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num4,        hui::Event::KeyboardButton::Num4);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num5,        hui::Event::KeyboardButton::Num5);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num6,        hui::Event::KeyboardButton::Num6);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num7,        hui::Event::KeyboardButton::Num7);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num8,        hui::Event::KeyboardButton::Num8);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Num9,        hui::Event::KeyboardButton::Num9);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Escape,      hui::Event::KeyboardButton::Escape);               
        CASE_RET_TYPE_(sf::Keyboard::Key::LControl,    hui::Event::KeyboardButton::LControl);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::LShift,      hui::Event::KeyboardButton::LShift);               
        CASE_RET_TYPE_(sf::Keyboard::Key::LAlt,        hui::Event::KeyboardButton::LAlt);               
        CASE_RET_TYPE_(sf::Keyboard::Key::LSystem,     hui::Event::KeyboardButton::LSystem);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::RControl,    hui::Event::KeyboardButton::RControl);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::RShift,      hui::Event::KeyboardButton::RShift);               
        CASE_RET_TYPE_(sf::Keyboard::Key::RAlt,        hui::Event::KeyboardButton::RAlt);               
        CASE_RET_TYPE_(sf::Keyboard::Key::RSystem,     hui::Event::KeyboardButton::RSystem);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Menu,        hui::Event::KeyboardButton::Menu);               
        CASE_RET_TYPE_(sf::Keyboard::Key::LBracket,    hui::Event::KeyboardButton::LBracket);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::RBracket,    hui::Event::KeyboardButton::RBracket);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Semicolon,   hui::Event::KeyboardButton::Semicolon);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Comma,       hui::Event::KeyboardButton::Comma);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Period,      hui::Event::KeyboardButton::Period);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Quote,       hui::Event::KeyboardButton::Quote);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Slash,       hui::Event::KeyboardButton::Slash);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Backslash,   hui::Event::KeyboardButton::Backslash);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Tilde,       hui::Event::KeyboardButton::Tilde);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Equal,       hui::Event::KeyboardButton::Equal);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Hyphen,      hui::Event::KeyboardButton::Hyphen);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Space,       hui::Event::KeyboardButton::Space);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Enter,       hui::Event::KeyboardButton::Enter);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Backspace,   hui::Event::KeyboardButton::Backspace);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Tab,         hui::Event::KeyboardButton::Tab);               
        CASE_RET_TYPE_(sf::Keyboard::Key::PageUp,      hui::Event::KeyboardButton::PageUp);               
        CASE_RET_TYPE_(sf::Keyboard::Key::PageDown,    hui::Event::KeyboardButton::PageDown);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::End,         hui::Event::KeyboardButton::End);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Home,        hui::Event::KeyboardButton::Home);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Insert,      hui::Event::KeyboardButton::Insert);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Delete,      hui::Event::KeyboardButton::Delete);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Add,         hui::Event::KeyboardButton::Add);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Subtract,    hui::Event::KeyboardButton::Subtract);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Multiply,    hui::Event::KeyboardButton::Multiply);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Divide,      hui::Event::KeyboardButton::Divide);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Left,        hui::Event::KeyboardButton::Left);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Right,       hui::Event::KeyboardButton::Right);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Up,          hui::Event::KeyboardButton::Up);           
        CASE_RET_TYPE_(sf::Keyboard::Key::Down,        hui::Event::KeyboardButton::Down);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad0,     hui::Event::KeyboardButton::Numpad0);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad1,     hui::Event::KeyboardButton::Numpad1);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad2,     hui::Event::KeyboardButton::Numpad2);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad3,     hui::Event::KeyboardButton::Numpad3);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad4,     hui::Event::KeyboardButton::Numpad4);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad5,     hui::Event::KeyboardButton::Numpad5);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad6,     hui::Event::KeyboardButton::Numpad6);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad7,     hui::Event::KeyboardButton::Numpad7);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad8,     hui::Event::KeyboardButton::Numpad8);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad9,     hui::Event::KeyboardButton::Numpad9);                   
        CASE_RET_TYPE_(sf::Keyboard::Key::F1,          hui::Event::KeyboardButton::F1);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F2,          hui::Event::KeyboardButton::F2);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F3,          hui::Event::KeyboardButton::F3);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F4,          hui::Event::KeyboardButton::F4);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F5,          hui::Event::KeyboardButton::F5);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F6,          hui::Event::KeyboardButton::F6);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F7,          hui::Event::KeyboardButton::F7);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F8,          hui::Event::KeyboardButton::F8);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F9,          hui::Event::KeyboardButton::F9);           
        CASE_RET_TYPE_(sf::Keyboard::Key::F10,         hui::Event::KeyboardButton::F10);               
        CASE_RET_TYPE_(sf::Keyboard::Key::F11,         hui::Event::KeyboardButton::F11);               
        CASE_RET_TYPE_(sf::Keyboard::Key::F12,         hui::Event::KeyboardButton::F12);               
        CASE_RET_TYPE_(sf::Keyboard::Key::F13,         hui::Event::KeyboardButton::F13);               
        CASE_RET_TYPE_(sf::Keyboard::Key::F14,         hui::Event::KeyboardButton::F14);               
        CASE_RET_TYPE_(sf::Keyboard::Key::F15,         hui::Event::KeyboardButton::F15);               
        CASE_RET_TYPE_(sf::Keyboard::Key::Pause,       hui::Event::KeyboardButton::Pause);               
        default:
            throw std::overflow_error("Unknown KeyboardButton type");
    }
    throw std::overflow_error("Unknown KeyboardButton type");
}

#undef CASE_RET_TYPE_

hui::Vector2d hui::Event::GetMouseCoord() const noexcept {
    const auto* event = static_cast<const hui::EventImpl*>(GetImpl());
    return {static_cast<double>(event->mouseMove.x), static_cast<double>(event->mouseMove.y)};
}