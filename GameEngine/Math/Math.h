#pragma once

#define PI  3.14159265358979323846f

class Math
{
public:
    static int Lerp(int a, int b, float t)
    {
        return static_cast<int>(static_cast<float>(a) + t * static_cast<float>(b - a));
    }

    static float InverseLerp(float a, float b, float v)
    {
        return (v - a) / (b - a);
    }

    static float EaseOutCubic(float x)
    {
        return 1.f - std::pow(1.f - x, 3.f);
    }

    static float EaseInCubic(float x)
    {
        return x * x * x;
    }

    static float EaseOutSin(float x)
    {
        return std::sin((x * PI) / 2.f);
    }

    static float EaseInSin(float x)
    {
        return 1.f - std::cos((x * PI) / 2.f);
    }
};
