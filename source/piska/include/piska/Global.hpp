#ifndef OPTOR_SOURCE_PISKA_INCLUDE_PISKA_GLOBAL_HPP
#define OPTOR_SOURCE_PISKA_INCLUDE_PISKA_GLOBAL_HPP

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

}

}

#endif /*OPTOR_SOURCE_PISKA_INCLUDE_PISKA_GLOBAL_HPP*/