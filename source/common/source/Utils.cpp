#include <numbers>

#include "common/Utils.hpp"

double common::Deg2Rad(double deg) noexcept{
    static constexpr double factor = std::numbers::pi / 180;
    return deg * factor;
}
double common::Rad2Deg(double rad) noexcept{
    static constexpr double factor = 180 / std::numbers::pi;
    return rad * factor;
}