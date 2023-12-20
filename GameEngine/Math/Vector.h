#pragma once
#include <string>

class Vector
{
public:
    float x;
    float y;

    Vector()
    {
        x = 0;
        y = 0;
    }
    
    Vector(float x, float y) : x(x), y(y)
    {
    }

    bool operator==(const Vector& point) const;
    std::string ToString() const;
};
