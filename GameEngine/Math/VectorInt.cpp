#include "VectorInt.h"

bool VectorInt::operator==(const VectorInt& point) const
{
    return this->x == point.x && this->y == point.y;
}

std::string VectorInt::ToString() const
{
    std::string o = "(";
    o += std::to_string(x);
    o += ", ";
    o += std::to_string(y);
    o += ")";
    return o;
}