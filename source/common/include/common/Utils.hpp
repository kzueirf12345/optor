#ifndef OPTOR_SOURCE_COMMON_INCLUDE_COMMON_UTILS_HPP
#define  OPTOR_SOURCE_COMMON_INCLUDE_COMMON_UTILS_HPP

#include <string>

namespace common 
{

[[nodiscard]] double Deg2Rad(double deg) noexcept;
[[nodiscard]] double Rad2Deg(double rad) noexcept;

std::string to_string(double value);

}

#endif /*OPTOR_SOURCE_COMMON_INCLUDE_COMMON_UTILS_HPP*/