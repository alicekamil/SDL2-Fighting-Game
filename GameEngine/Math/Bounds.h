#pragma once

struct Bounds
{
    float x;
    float y;
    float w;
    float h;

    Bounds(float x, float y, float w, float h)
        : x(x),
          y(y),
          w(w),
          h(h)
    {
    }

    bool CollidesWith(Bounds other);
};
