#pragma once
#include <vector>

#include "AnimationName.h"
#include "Keyframe.h"

struct Animation
{
    AnimationName animationName;
    int frameCount;
    float length;
    bool shouldLoop = true;
    std::vector<Keyframe> keyframes;
};
