#include <chrono>
#include <optional>
#include <thread>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "SFML/Window/Mouse.hpp"

#include "dr4Plugin/Window.hpp"
#include "dr4Plugin/Font.hpp"
#include "dr4Plugin/Image.hpp"
#include "dr4Plugin/Texture.hpp"
#include "dr4Plugin/Line.hpp"
#include "dr4Plugin/Circle.hpp"

#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/mouse_buttons.hpp"
#include "dr4/texture.hpp"

#include "common/ErrorHandler.hpp"

static dr4::MouseButtonType MouseCodeSF2DR4(sf::Mouse::Button code) noexcept;
static dr4::KeyCode           KeyCodeSF2DR4(sf::Keyboard::Key code) noexcept;
static dr4::KeyMode           KeyModeSF2DR4(sf::Event::KeyEvent event) noexcept;

size_t EncodeUTF8(uint32_t cp, char out[5]);

optor::dr4::Window::Window()
    :   window_{},
        size_{2400, 1100},
        title_{"0xCEBAEBALDEDA"},
        ctorTime_(std::chrono::high_resolution_clock::now()),
        utf8_buffer_()
{}

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
    return {static_cast<float>(size_.x), static_cast<float>(size_.y)};
}

void optor::dr4::Window::SetSize(::dr4::Vec2f size)
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
        window_.setFramerateLimit(60);
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

void optor::dr4::Window::Clear(::dr4::Color color) 
{
    ERROR_HANDLE([this, &color](){
        window_.clear(sf::Color(color.r, color.g, color.b, color.a));
    });
}

void optor::dr4::Window::Draw(const ::dr4::Texture &texture) {
    const optor::dr4::Texture& myTexture = dynamic_cast<const optor::dr4::Texture&>(texture);

    ERROR_HANDLE([this, &myTexture](){
        window_.draw(
            myTexture.sprite_,
            sf::RenderStates().transform.translate(
                myTexture.pos_.x, 
                myTexture.pos_.y
            )
        );
    });
}

void optor::dr4::Window::Display() 
{
    ERROR_HANDLE([this](){
        window_.display();
    });
}

double optor::dr4::Window::GetTime() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - ctorTime_
    ).count() / 1000000.f;
}

void optor::dr4::Window::Sleep(double time) {
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int64_t>(time * 1000000)));
}

::dr4::Texture  *optor::dr4::Window::CreateTexture()    {
    return new optor::dr4::Texture();
}
::dr4::Image    *optor::dr4::Window::CreateImage()      {
    return new optor::dr4::Image();
}
::dr4::Font     *optor::dr4::Window::CreateFont()       {
    return new optor::dr4::Font();
}
::dr4::Line      *optor::dr4::Window::CreateLine()      {
    return new optor::dr4::Line();
}
::dr4::Circle    *optor::dr4::Window::CreateCircle()    {
    return new optor::dr4::Circle();
}
::dr4::Rectangle *optor::dr4::Window::CreateRectangle() {
    return new optor::dr4::Rectangle();
}
::dr4::Text      *optor::dr4::Window::CreateText()      {
    return new optor::dr4::Text();
}

void optor::dr4::Window::StartTextInput() {
    //PASS
}
void optor::dr4::Window::StopTextInput() {
    //PASS
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
            static ::dr4::Vec2f prevMouseCoord = {0, 0};

            event.type = ::dr4::Event::Type::MOUSE_MOVE;
            event.mouseMove = {
                .pos = {
                    static_cast<float>(eventSF.mouseMove.x), 
                    static_cast<float>(eventSF.mouseMove.y)
                },
                .rel= {
                    static_cast<float>(eventSF.mouseMove.x - prevMouseCoord.x), 
                    static_cast<float>(eventSF.mouseMove.y - prevMouseCoord.y)
                }
            };
            prevMouseCoord = event.mouseMove.pos;
            break;
        }

        case sf::Event::EventType::MouseButtonPressed: {
            event.type = ::dr4::Event::Type::MOUSE_DOWN;
            event.mouseButton = {
                .pos = {
                    static_cast<float>(eventSF.mouseButton.x), 
                    static_cast<float>(eventSF.mouseButton.y)
                }
            };
            event.mouseButton.button = MouseCodeSF2DR4(eventSF.mouseButton.button);
            break;
        }

        case sf::Event::EventType::MouseButtonReleased: {
            event.type = ::dr4::Event::Type::MOUSE_UP;
            event.mouseButton = {
                .pos = {
                    static_cast<float>(eventSF.mouseButton.x), 
                    static_cast<float>(eventSF.mouseButton.y)
                }
            };
            event.mouseButton.button = MouseCodeSF2DR4(eventSF.mouseButton.button);
            break;
        }

        case sf::Event::EventType::MouseWheelScrolled: {
            event.type = ::dr4::Event::Type::MOUSE_WHEEL;
            event.mouseWheel = {
                .pos = {
                    static_cast<float>(eventSF.mouseWheel.x), 
                    static_cast<float>(eventSF.mouseWheel.y)
                }
            };

            if (eventSF.mouseWheelScroll.wheel == sf::Mouse::Wheel::HorizontalWheel) {
                event.mouseWheel.delta = {static_cast<float>(eventSF.mouseWheel.delta), 0};
            } else {
                event.mouseWheel.delta = {0, static_cast<float>(eventSF.mouseWheel.delta)};
            }

            break;
        }

        case sf::Event::EventType::KeyPressed: {
            event.type = ::dr4::Event::Type::KEY_DOWN;
            event.key.sym = KeyCodeSF2DR4(eventSF.key.code);
            event.key.mods = static_cast<uint16_t>(KeyModeSF2DR4(eventSF.key));
            break;
        }

        case sf::Event::EventType::KeyReleased: {
            event.type = ::dr4::Event::Type::KEY_UP;
            event.key.sym = KeyCodeSF2DR4(eventSF.key.code);
            event.key.mods = static_cast<uint16_t>(KeyModeSF2DR4(eventSF.key));
            break;
        }

        case sf::Event::EventType::TextEntered: {
            event.type = ::dr4::Event::Type::TEXT_EVENT;
            if (EncodeUTF8(eventSF.text.unicode, utf8_buffer_) == 0) {
                event.type = ::dr4::Event::Type::UNKNOWN;
                break;
            }
            event.text.unicode = utf8_buffer_;
            break;
        }

        case sf::Event::EventType::Closed: {
            event.type = ::dr4::Event::Type::QUIT;
            break;
        }

        default:
            event.type = ::dr4::Event::Type::UNKNOWN;
            break;
    }

    return event;
}

static dr4::KeyMode KeyModeSF2DR4(sf::Event::KeyEvent event) noexcept
{
    if (event.alt) {
        return dr4::KeyMode::KEYMOD_ALT;
    }

    if (event.shift) {
        return dr4::KeyMode::KEYMOD_SHIFT;
    }

    if (event.control) {
        return dr4::KeyMode::KEYMOD_CTRL;
    }

    return dr4::KeyMode::KEYMOD_NONE;
}   

#define CASE_RET_TYPE_(guiType, huiType) \
        case guiType: return huiType

static dr4::MouseButtonType MouseCodeSF2DR4(sf::Mouse::Button code) noexcept 
{
    switch (code) {
        CASE_RET_TYPE_(sf::Mouse::Button::Left,         dr4::MouseButtonType::LEFT);
        CASE_RET_TYPE_(sf::Mouse::Button::Right,        dr4::MouseButtonType::RIGHT);
        CASE_RET_TYPE_(sf::Mouse::Button::Middle,       dr4::MouseButtonType::MIDDLE);  
        default:
            return dr4::MouseButtonType::UNKNOWN;
    }
    return dr4::MouseButtonType::UNKNOWN;
}

static dr4::KeyCode KeyCodeSF2DR4(sf::Keyboard::Key code) noexcept 
{
    switch (code) {
        CASE_RET_TYPE_(sf::Keyboard::Key::A,            dr4::KEYCODE_A);
        CASE_RET_TYPE_(sf::Keyboard::Key::B,            dr4::KEYCODE_B);
        CASE_RET_TYPE_(sf::Keyboard::Key::C,            dr4::KEYCODE_C);
        CASE_RET_TYPE_(sf::Keyboard::Key::D,            dr4::KEYCODE_D);
        CASE_RET_TYPE_(sf::Keyboard::Key::E,            dr4::KEYCODE_E);
        CASE_RET_TYPE_(sf::Keyboard::Key::F,            dr4::KEYCODE_F);
        CASE_RET_TYPE_(sf::Keyboard::Key::G,            dr4::KEYCODE_G);
        CASE_RET_TYPE_(sf::Keyboard::Key::H,            dr4::KEYCODE_H);
        CASE_RET_TYPE_(sf::Keyboard::Key::I,            dr4::KEYCODE_I);
        CASE_RET_TYPE_(sf::Keyboard::Key::J,            dr4::KEYCODE_J);
        CASE_RET_TYPE_(sf::Keyboard::Key::K,            dr4::KEYCODE_K);
        CASE_RET_TYPE_(sf::Keyboard::Key::L,            dr4::KEYCODE_L);
        CASE_RET_TYPE_(sf::Keyboard::Key::M,            dr4::KEYCODE_M);
        CASE_RET_TYPE_(sf::Keyboard::Key::N,            dr4::KEYCODE_N);
        CASE_RET_TYPE_(sf::Keyboard::Key::O,            dr4::KEYCODE_O);
        CASE_RET_TYPE_(sf::Keyboard::Key::P,            dr4::KEYCODE_P);
        CASE_RET_TYPE_(sf::Keyboard::Key::Q,            dr4::KEYCODE_Q);
        CASE_RET_TYPE_(sf::Keyboard::Key::R,            dr4::KEYCODE_R);
        CASE_RET_TYPE_(sf::Keyboard::Key::S,            dr4::KEYCODE_S);
        CASE_RET_TYPE_(sf::Keyboard::Key::T,            dr4::KEYCODE_T);
        CASE_RET_TYPE_(sf::Keyboard::Key::U,            dr4::KEYCODE_U);
        CASE_RET_TYPE_(sf::Keyboard::Key::V,            dr4::KEYCODE_V);
        CASE_RET_TYPE_(sf::Keyboard::Key::W,            dr4::KEYCODE_W);
        CASE_RET_TYPE_(sf::Keyboard::Key::X,            dr4::KEYCODE_X);
        CASE_RET_TYPE_(sf::Keyboard::Key::Y,            dr4::KEYCODE_Y);
        CASE_RET_TYPE_(sf::Keyboard::Key::Z,            dr4::KEYCODE_Z);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num0,         dr4::KEYCODE_NUM0);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num1,         dr4::KEYCODE_NUM1);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num2,         dr4::KEYCODE_NUM2);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num3,         dr4::KEYCODE_NUM3);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num4,         dr4::KEYCODE_NUM4);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num5,         dr4::KEYCODE_NUM5);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num6,         dr4::KEYCODE_NUM6);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num7,         dr4::KEYCODE_NUM7);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num8,         dr4::KEYCODE_NUM8);
        CASE_RET_TYPE_(sf::Keyboard::Key::Num9,         dr4::KEYCODE_NUM9);
        CASE_RET_TYPE_(sf::Keyboard::Key::Escape,       dr4::KEYCODE_ESCAPE);
        CASE_RET_TYPE_(sf::Keyboard::Key::LControl,     dr4::KEYCODE_LCONTROL);
        CASE_RET_TYPE_(sf::Keyboard::Key::LShift,       dr4::KEYCODE_LSHIFT);
        CASE_RET_TYPE_(sf::Keyboard::Key::LAlt,         dr4::KEYCODE_LALT);
        CASE_RET_TYPE_(sf::Keyboard::Key::LSystem,      dr4::KEYCODE_LSYSTEM);
        CASE_RET_TYPE_(sf::Keyboard::Key::RControl,     dr4::KEYCODE_RCONTROL);
        CASE_RET_TYPE_(sf::Keyboard::Key::RShift,       dr4::KEYCODE_RSHIFT);
        CASE_RET_TYPE_(sf::Keyboard::Key::RAlt,         dr4::KEYCODE_RALT);
        CASE_RET_TYPE_(sf::Keyboard::Key::RSystem,      dr4::KEYCODE_RSYSTEM);
        CASE_RET_TYPE_(sf::Keyboard::Key::Menu,         dr4::KEYCODE_MENU);
        CASE_RET_TYPE_(sf::Keyboard::Key::LBracket,     dr4::KEYCODE_LBRACKET);
        CASE_RET_TYPE_(sf::Keyboard::Key::RBracket,     dr4::KEYCODE_RBRACKET);
        CASE_RET_TYPE_(sf::Keyboard::Key::Semicolon,    dr4::KEYCODE_SEMICOLON);
        CASE_RET_TYPE_(sf::Keyboard::Key::Comma,        dr4::KEYCODE_COMMA);
        CASE_RET_TYPE_(sf::Keyboard::Key::Period,       dr4::KEYCODE_PERIOD);
        CASE_RET_TYPE_(sf::Keyboard::Key::Quote,        dr4::KEYCODE_QUOTE);
        CASE_RET_TYPE_(sf::Keyboard::Key::Slash,        dr4::KEYCODE_SLASH);
        CASE_RET_TYPE_(sf::Keyboard::Key::Backslash,    dr4::KEYCODE_BACKSLASH);
        CASE_RET_TYPE_(sf::Keyboard::Key::Tilde,        dr4::KEYCODE_TILDE);
        CASE_RET_TYPE_(sf::Keyboard::Key::Equal,        dr4::KEYCODE_EQUAL);
        CASE_RET_TYPE_(sf::Keyboard::Key::Hyphen,       dr4::KEYCODE_HYPHEN);
        CASE_RET_TYPE_(sf::Keyboard::Key::Space,        dr4::KEYCODE_SPACE);
        CASE_RET_TYPE_(sf::Keyboard::Key::Enter,        dr4::KEYCODE_ENTER);
        CASE_RET_TYPE_(sf::Keyboard::Key::Backspace,    dr4::KEYCODE_BACKSPACE);
        CASE_RET_TYPE_(sf::Keyboard::Key::Tab,          dr4::KEYCODE_TAB);
        CASE_RET_TYPE_(sf::Keyboard::Key::PageUp,       dr4::KEYCODE_PAGEUP);
        CASE_RET_TYPE_(sf::Keyboard::Key::PageDown,     dr4::KEYCODE_PAGEDOWN);
        CASE_RET_TYPE_(sf::Keyboard::Key::End,          dr4::KEYCODE_END);
        CASE_RET_TYPE_(sf::Keyboard::Key::Home,         dr4::KEYCODE_HOME);
        CASE_RET_TYPE_(sf::Keyboard::Key::Insert,       dr4::KEYCODE_INSERT);
        CASE_RET_TYPE_(sf::Keyboard::Key::Delete,       dr4::KEYCODE_DELETE);
        CASE_RET_TYPE_(sf::Keyboard::Key::Add,          dr4::KEYCODE_ADD);
        CASE_RET_TYPE_(sf::Keyboard::Key::Subtract,     dr4::KEYCODE_SUBTRACT);
        CASE_RET_TYPE_(sf::Keyboard::Key::Multiply,     dr4::KEYCODE_MULTIPLY);
        CASE_RET_TYPE_(sf::Keyboard::Key::Divide,       dr4::KEYCODE_DIVIDE);
        CASE_RET_TYPE_(sf::Keyboard::Key::Left,         dr4::KEYCODE_LEFT);
        CASE_RET_TYPE_(sf::Keyboard::Key::Right,        dr4::KEYCODE_RIGHT);
        CASE_RET_TYPE_(sf::Keyboard::Key::Up,           dr4::KEYCODE_UP);
        CASE_RET_TYPE_(sf::Keyboard::Key::Down,         dr4::KEYCODE_DOWN);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad0,      dr4::KEYCODE_NUMPAD0);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad1,      dr4::KEYCODE_NUMPAD1);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad2,      dr4::KEYCODE_NUMPAD2);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad3,      dr4::KEYCODE_NUMPAD3);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad4,      dr4::KEYCODE_NUMPAD4);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad5,      dr4::KEYCODE_NUMPAD5);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad6,      dr4::KEYCODE_NUMPAD6);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad7,      dr4::KEYCODE_NUMPAD7);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad8,      dr4::KEYCODE_NUMPAD8);
        CASE_RET_TYPE_(sf::Keyboard::Key::Numpad9,      dr4::KEYCODE_NUMPAD9);
        CASE_RET_TYPE_(sf::Keyboard::Key::F1,           dr4::KEYCODE_F1);
        CASE_RET_TYPE_(sf::Keyboard::Key::F2,           dr4::KEYCODE_F2);
        CASE_RET_TYPE_(sf::Keyboard::Key::F3,           dr4::KEYCODE_F3);
        CASE_RET_TYPE_(sf::Keyboard::Key::F4,           dr4::KEYCODE_F4);
        CASE_RET_TYPE_(sf::Keyboard::Key::F5,           dr4::KEYCODE_F5);
        CASE_RET_TYPE_(sf::Keyboard::Key::F6,           dr4::KEYCODE_F6);
        CASE_RET_TYPE_(sf::Keyboard::Key::F7,           dr4::KEYCODE_F7);
        CASE_RET_TYPE_(sf::Keyboard::Key::F8,           dr4::KEYCODE_F8);
        CASE_RET_TYPE_(sf::Keyboard::Key::F9,           dr4::KEYCODE_F9);
        CASE_RET_TYPE_(sf::Keyboard::Key::F10,          dr4::KEYCODE_F10);
        CASE_RET_TYPE_(sf::Keyboard::Key::F11,          dr4::KEYCODE_F11);
        CASE_RET_TYPE_(sf::Keyboard::Key::F12,          dr4::KEYCODE_F12);
        CASE_RET_TYPE_(sf::Keyboard::Key::F13,          dr4::KEYCODE_F13);
        CASE_RET_TYPE_(sf::Keyboard::Key::F14,          dr4::KEYCODE_F14);
        CASE_RET_TYPE_(sf::Keyboard::Key::F15,          dr4::KEYCODE_F15);
        CASE_RET_TYPE_(sf::Keyboard::Key::Pause,        dr4::KEYCODE_PAUSE);
        default:
            return dr4::KEYCODE_UNKNOWN;
    }
    return dr4::KEYCODE_UNKNOWN;
}

#undef CASE_RET_TYPE_

size_t EncodeUTF8(uint32_t cp, char out[5]) {
    if (cp > 0x10FFFFu) return 0;
    if (cp >= 0xD800u && cp <= 0xDFFFu) return 0;

    if (cp <= 0x7Fu) {
        out[0] = static_cast<char>(cp);
        out[1] = '\0';
        return 1;
    }
    if (cp <= 0x7FFu) {
        out[0] = static_cast<char>(0xC0u | (cp >> 6));
        out[1] = static_cast<char>(0x80u | (cp & 0x3Fu));
        out[2] = '\0';
        return 2;
    }
    if (cp <= 0xFFFFu) {
        out[0] = static_cast<char>(0xE0u | (cp >> 12));
        out[1] = static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu));
        out[2] = static_cast<char>(0x80u | (cp & 0x3Fu));
        out[3] = '\0';
        return 3;
    }
    out[0] = static_cast<char>(0xF0u | (cp >> 18));
    out[1] = static_cast<char>(0x80u | ((cp >> 12) & 0x3Fu));
    out[2] = static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu));
    out[3] = static_cast<char>(0x80u | (cp & 0x3Fu));
    out[4] = '\0';
    return 4;
}