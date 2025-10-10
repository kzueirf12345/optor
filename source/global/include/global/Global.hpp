#ifndef OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP
#define OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP


#include "hui/Color.hpp"

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
#endif /*OPTOR_PALETE_NAME*/

}

static constexpr inline double PROGRAM_WIDTH = 1400;
static constexpr inline double PROGRAM_HEIGHT = 900;

static constexpr inline double INIT_WIDGET_BORDER_THICKNESS = 5;

}

#endif /*OPTOR_SOURCE_GLOBAL_INCLUDE_GLOBAL_GLOBAL_HPP*/