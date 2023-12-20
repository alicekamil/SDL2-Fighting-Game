#include "Vector.h"

bool Vector::operator==(const Vector& point) const
{
    return this->x == point.x && this->y == point.y;
}

std::string Vector::ToString() const
{
    std::string o = "(";
    o += std::to_string(x);
    o += ", ";
    o += std::to_string(y);
    o += ")";
    return o;
}