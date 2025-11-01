#include "dr4/math/rect.hpp"

bool ::dr4::Rect2f::Contains(::dr4::Vec2f point) const
{
    return this->pos.x <= point.x && point.x <= this->pos.x + this->size.x
        && this->pos.y <= point.y && point.y <= this->pos.y + this->size.y;
}