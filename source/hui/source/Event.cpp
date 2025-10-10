#include <SFML/Window/Event.hpp>
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
#undef CASE_RET_TYPE_