#pragma once
#include <string>

class VectorInt
{
public:
    int x;
    int y;

    VectorInt()
    {
        x = 0;
        y = 0;
    }
    
    VectorInt(int x, int y) : x(x), y(y)
    {
    }

    bool operator==(const VectorInt& point) const;
    std::string ToString() const;
};
