#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_GLOBAL_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_GLOBAL_HPP

#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/mouse_buttons.hpp"

namespace optor 
{
namespace pp 
{

enum class Side {
    UNKNOWN = -1,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

inline static constexpr float OutlineThickness = 5;
inline static const dr4::Vec2f OutlineThicknessVec = {
    optor::pp::OutlineThickness,
    optor::pp::OutlineThickness
};

inline static const constexpr dr4::MouseButtonType CREATE_BUTTON = dr4::MouseButtonType::LEFT;

static const ::dr4::Color WindowBackground(0x20, 0x21, 0x2d, 0xff);
static const ::dr4::Color WindowBorder(0x41, 0x42, 0x5a, 0xff);

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_GLOBAL_HPP*/