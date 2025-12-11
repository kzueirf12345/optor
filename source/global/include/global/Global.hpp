#ifndef OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP
#define OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP

#include <string>

#include "dr4/keycodes.hpp"
#include "dr4/mouse_buttons.hpp"
#include "dr4/math/color.hpp"

#include "dr4/texture.hpp"
#include "optics/Material.hpp"

namespace optor 
{

namespace color 
{

#if !defined(OPTOR_PALETE_NAME)
#define OPTOR_PALETE_NAME TNC
#endif /*OPTOR_PALETE_NAME*/

#if OPTOR_PALETE_NAME == TNC
    static const ::dr4::Color ProgramBackground(0x16, 0x17, 0x20, 0xff);

    static const ::dr4::Color WindowBackground(0x20, 0x21, 0x2d, 0xff);
    static const ::dr4::Color WindowBorder(0x41, 0x42, 0x5a, 0xff);

    static const ::dr4::Color TextPrimary(0xc0, 0xca, 0xf5, 0xff);

    static const ::dr4::Color ButtonReleased(0x28, 0x29, 0x3d, 0xff);
    static const ::dr4::Color ButtonPressed(0x35, 0x36, 0x4e, 0xff);
    static const ::dr4::Color ButtonIdle(0x24, 0x25, 0x36, 0xff);
    static const ::dr4::Color ScrollBarThumb(0x41, 0x42, 0x5a, 0xff);

    static const ::dr4::Color Red(0xf7, 0x76, 0x8e, 0xff);
    static const ::dr4::Color Green(0x9e, 0xce, 0x6a, 0xff);
    static const ::dr4::Color Blue(0x7a, 0xa2, 0xf7, 0xff);
    static const ::dr4::Color Yellow(0xe0, 0xaf, 0x68, 0xff);
    static const ::dr4::Color Purple(0xbb, 0x9a, 0xf7, 0xff);
    static const ::dr4::Color Cyan(0x7d, 0xcf, 0xff, 0xff);
    static const ::dr4::Color Orange(0xff, 0x9e, 0x64, 0xff);
    static const ::dr4::Color Pink(0xf5, 0x76, 0xc0, 0xff);
    static const ::dr4::Color GrayLight(0x56, 0x5a, 0x89, 0xff);
    static const ::dr4::Color Gray(0x41, 0x42, 0x5a, 0xff);
    static const ::dr4::Color GrayDark(0x1a, 0x1b, 0x26, 0xff);
    static const ::dr4::Color Black(0x16, 0x17, 0x20, 0xff);

    static const ::dr4::Color Success(0x9e, 0xce, 0x6a, 0xff);
    static const ::dr4::Color Warning(0xe0, 0xaf, 0x68, 0xff);
    static const ::dr4::Color Error(0xf7, 0x76, 0x8e, 0xff);
    static const ::dr4::Color Info(0x7a, 0xa2, 0xf7, 0xff);

    static const ::dr4::Color Poison(0xbf, 0x00, 0xff, 0xff);

#endif /*OPTOR_PALETE_NAME*/

static const ::dr4::Color Transparent(0x0, 0x0, 0x0, 0x0);
static const ::dr4::Color White(0xff, 0xff, 0xff, 0xff);

}

namespace materials 
{

const optor::Material LIGHT          ({1.,   1.,   1.},   {0.,  0.,  0.},  {0.,  0.,  0.},     0.,     0.,  0.,  0. );
const optor::Material SELECTOR       ({1,    0,    0.},   {1  , 0  , 0  }, {1  , 0  , 0  },    0   ,   0  , 0  , 0  );
const optor::Material IVORY          ({0.1,  0.1,  0.1},  {0.4, 0.4, 0.3}, {1.0, 1.0, 1.0},    50.0,   0.1, 1.0, 0.0);
const optor::Material GLASS          ({0.05, 0.05, 0.05}, {0.6, 0.7, 0.8}, {1.0, 1.0, 1.0},    125.0,  0.1, 1.5, 0.8);
const optor::Material RED_RUBBER     ({0.05, 0.01, 0.01}, {0.3, 0.1, 0.1}, {0.3, 0.3, 0.3},    10.0,   0.0, 1.0, 0.0);
const optor::Material MIRROR         ({0.05, 0.05, 0.05}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0},    1425.0, 0.8, 1.0, 0.0);
const optor::Material WOOD           ({0.05, 0.03, 0.01}, {0.4, 0.25,0.1}, {0.2, 0.2, 0.2},    25.0,   0.0, 1.0, 0.0);
const optor::Material STEEL          ({0.1,  0.1,  0.1},  {0.5, 0.5, 0.5}, {0.7, 0.7, 0.7},    200.0,  0.6, 1.0, 0.0);
const optor::Material PLASTIC        ({0.02, 0.02, 0.02}, {0.3, 0.3, 0.3}, {0.1, 0.1, 0.1},    15.0,   0.0, 1.0, 0.0);
const optor::Material FABRIC         ({0.03, 0.02, 0.02}, {0.4, 0.2, 0.2}, {0.05,0.05,0.05},   5.0,    0.0, 1.0, 0.0);
const optor::Material MATTE_GLASS    ({0.05, 0.05, 0.05}, {0.5, 0.5, 0.55},{0.3, 0.3, 0.3},    50.0,   0.1, 1.3, 0.5);

}

static constexpr inline double EPSILON = 1e-8;

static constexpr inline double PROGRAM_WIDTH  = 2300;
static constexpr inline double PROGRAM_HEIGHT = 1100;

static constexpr inline unsigned int FRAME_LIMIT = 20;

static constexpr inline float INIT_WIDGET_BORDER_THICKNESS = 5;
static constexpr inline float INIT_HEADER_HEIGHT = 35;
static constexpr inline float INIT_SCROLLBAR_WIDTH = 28;

static constexpr inline ::dr4::MouseButtonType    INIT_DRAG_WINDOW_BUTTON_         = ::dr4::MouseButtonType::MIDDLE;
static constexpr inline ::dr4::MouseButtonType    INIT_SELECT_WINDOW_BUTTON_       = ::dr4::MouseButtonType::LEFT;
static constexpr inline ::dr4::KeyCode            INIT_UNSELECT_WINDOW_BUTTON_     = ::dr4::KEYCODE_ESCAPE;
static constexpr inline ::dr4::MouseButtonType    INIT_PRESS_BUTTON_BUTTON_        = ::dr4::MouseButtonType::LEFT;

static constexpr inline double CAMERA_MOVE_SPEED   = 1;
static constexpr inline double CAMERA_ROTATE_SPEED = 0.1;

static constexpr inline double GLOBAL_AMBIENT_COEF = 0.4;


static const inline std::string FONT_PATH = "/usr/share/fonts/TTF/CaskaydiaCoveNerdFontMono-Regular.ttf";

extern ::dr4::Font* FONT;

static constexpr inline float STRING_BLOCK_HEIGHT = 28.;

}

#endif /*OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP*/