#ifndef OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP
#define OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP

#include "hui/Color.hpp"
#include "hui/Event.hpp"

namespace optor 
{

namespace color 
{

#if !defined(OPTOR_PALETE_NAME)
#define OPTOR_PALETE_NAME TNC
#endif /*OPTOR_PALETE_NAME*/

#if OPTOR_PALETE_NAME == TNC
    static const hui::Color ProgramBackground(0x16, 0x17, 0x20);

    static const hui::Color WindowBackground(0x1a, 0x1b, 0x26);
    static const hui::Color WindowBorder(0x41, 0x42, 0x5a);

    static const hui::Color TextPrimary(0xc0, 0xca, 0xf5);
    
    static const hui::Color TextSecondary(0x78, 0x7c, 0x99);
    static const hui::Color TextDisabled(0x54, 0x58, 0x76);
    
    static const hui::Color AccentBlue(0x7a, 0xa2, 0xf7);
    static const hui::Color AccentCyan(0x7d, 0xcf, 0xff);
    static const hui::Color AccentGreen(0x9e, 0xce, 0x6a);
    static const hui::Color AccentYellow(0xe0, 0xaf, 0x68);
    static const hui::Color AccentOrange(0xff, 0x9e, 0x64);
    static const hui::Color AccentRed(0xf7, 0x76, 0x8e);
    static const hui::Color AccentMagenta(0xbb, 0x9a, 0xf7);
    
    static const hui::Color ButtonBackground(0x1f, 0x20, 0x32);
    static const hui::Color ButtonHover(0x28, 0x29, 0x40);
    static const hui::Color ButtonActive(0x2e, 0x30, 0x4a);
    
    static const hui::Color InputBackground(0x16, 0x17, 0x20);
    static const hui::Color InputBorder(0x3b, 0x3d, 0x54);
    
    static const hui::Color SelectionBackground(0x2e, 0x30, 0x4a);
    static const hui::Color HighlightBackground(0x33, 0x35, 0x52);
#endif /*OPTOR_PALETE_NAME*/

static const hui::Color Transparent(0x0, 0x0, 0x0, 0x0);
static const hui::Color White(0xff, 0xff, 0xff, 0xff);

}


static constexpr inline double PROGRAM_WIDTH  = 1400;
static constexpr inline double PROGRAM_HEIGHT = 900;

static constexpr inline unsigned int FRAME_LIMIT = 20;

static constexpr inline double INIT_WIDGET_BORDER_THICKNESS = 5;

static constexpr inline hui::Event::MouseButton    INIT_DRAG_WINDOW_BUTTON_     = hui::Event::MouseButton::Middle;
static constexpr inline hui::Event::MouseButton    INIT_SELECT_WINDOW_BUTTON_   = hui::Event::MouseButton::Left;
static constexpr inline hui::Event::KeyboardButton INIT_UNSELECT_WINDOW_BUTTON_ = hui::Event::KeyboardButton::Escape;

static constexpr inline double CAMERA_MOVE_SPEED   = 1;
static constexpr inline double CAMERA_ROTATE_SPEED = 0.1;

static constexpr inline double GLOBAL_AMBIENT_COEF = 0.4;

}

#endif /*OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP*/