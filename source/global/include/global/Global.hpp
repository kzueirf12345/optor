#ifndef OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP
#define OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP

#include "hui/Color.hpp"
#include "hui/Event.hpp"
#include "optics/Material.hpp"
#include "hui/Font.hpp"

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
    
    static const hui::Color Red(0xf7, 0x76, 0x8e);
    static const hui::Color Green(0x9e, 0xce, 0x6a);
    static const hui::Color Blue(0x7a, 0xa2, 0xf7);
    static const hui::Color Yellow(0xe0, 0xaf, 0x68);
    static const hui::Color Purple(0xbb, 0x9a, 0xf7);
    static const hui::Color Cyan(0x7d, 0xcf, 0xff);
    static const hui::Color Orange(0xff, 0x9e, 0x64);
    static const hui::Color Pink(0xf5, 0x76, 0xc0);
    
    static const hui::Color GrayLight(0x56, 0x5a, 0x89);
    static const hui::Color Gray(0x41, 0x42, 0x5a);
    static const hui::Color GrayDark(0x1a, 0x1b, 0x26);
    static const hui::Color Black(0x16, 0x17, 0x20);
    
    static const hui::Color Success(0x9e, 0xce, 0x6a);
    static const hui::Color Warning(0xe0, 0xaf, 0x68);
    static const hui::Color Error(0xf7, 0x76, 0x8e);
    static const hui::Color Info(0x7a, 0xa2, 0xf7);

    static const hui::Color Poison(0xbf, 0x00, 0xff);

#endif /*OPTOR_PALETE_NAME*/

static const hui::Color Transparent(0x0, 0x0, 0x0, 0x0);
static const hui::Color White(0xff, 0xff, 0xff, 0xff);

}

namespace materials 
{
    const optor::Material LIGHT          ({1, 1, 1},          {0, 0, 0},       {0, 0, 0},          0,      0,   0,   0);
    const optor::Material IVORY          ({0.1, 0.1, 0.1},    {0.4, 0.4, 0.3}, {1.0, 1.0, 1.0},    50.0,   0.1, 1.0, 0.0);
    const optor::Material GLASS          ({0.05, 0.05, 0.05}, {0.6, 0.7, 0.8}, {1.0, 1.0, 1.0},    125.0,  0.1, 1.5, 0.8);
    const optor::Material RED_RUBBER     ({0.05, 0.01, 0.01}, {0.3, 0.1, 0.1}, {0.3, 0.3, 0.3},    10.0,   0.0, 1.0, 0.0);
    const optor::Material MIRROR         ({0.05, 0.05, 0.05}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0},    1425.0, 0.8, 1.0, 0.0);
    const optor::Material WOOD           ({0.05, 0.03, 0.01}, {0.4, 0.25, 0.1},{0.2, 0.2, 0.2},    25.0,   0.0, 1.0, 0.0);
    const optor::Material STEEL          ({0.1, 0.1, 0.1},    {0.5, 0.5, 0.5}, {0.7, 0.7, 0.7},    200.0,  0.6, 1.0, 0.0);
    const optor::Material PLASTIC        ({0.02, 0.02, 0.02}, {0.3, 0.3, 0.3}, {0.1, 0.1, 0.1},    15.0,   0.0, 1.0, 0.0);
    const optor::Material FABRIC         ({0.03, 0.02, 0.02}, {0.4, 0.2, 0.2}, {0.05, 0.05, 0.05}, 5.0,    0.0, 1.0, 0.0);
    const optor::Material MATTE_GLASS    ({0.05, 0.05, 0.05}, {0.5, 0.5, 0.55},{0.3, 0.3, 0.3},    50.0,   0.1, 1.3, 0.5);
}

static constexpr inline double EPSILON = 1e-8;

static constexpr inline double PROGRAM_WIDTH  = 2200;
static constexpr inline double PROGRAM_HEIGHT = 900;

static constexpr inline unsigned int FRAME_LIMIT = 20;

static constexpr inline double INIT_WIDGET_BORDER_THICKNESS = 5;

static constexpr inline hui::Event::MouseButton    INIT_DRAG_WINDOW_BUTTON_         = hui::Event::MouseButton::Middle;
static constexpr inline hui::Event::MouseButton    INIT_SELECT_WINDOW_BUTTON_       = hui::Event::MouseButton::Left;
static constexpr inline hui::Event::KeyboardButton INIT_UNSELECT_WINDOW_BUTTON_     = hui::Event::KeyboardButton::Escape;
static constexpr inline hui::Event::MouseButton    INIT_PRESS_BUTTON_BUTTON_        = hui::Event::MouseButton::Left;

static constexpr inline double CAMERA_MOVE_SPEED   = 1;
static constexpr inline double CAMERA_ROTATE_SPEED = 0.1;

static constexpr inline double GLOBAL_AMBIENT_COEF = 0.4;


static const inline std::string FONT_PATH = "./assets/TokyoNight.ttf";

static const inline hui::Font FONT(FONT_PATH);

}

#endif /*OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP*/