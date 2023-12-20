#pragma once
#include <functional>
#include "AnimationName.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/ObjectRenderer.h"

struct Keyframe
{

    Keyframe(float time, int frame_index)
        : time(time),
          frameIndex(frame_index)
    {
    }

    Keyframe(float time, int frame_index, const std::function<void(GameObject*)>& function)
        : time(time),
          frameIndex(frame_index),
          function(function)
    {
    }
    

    float time;
    int frameIndex;

    std::function<void(GameObject*)> function = [](GameObject*){};
    
    virtual void Execute(GameObject* gameObject, AnimationName animationName)
    {
        function(gameObject);
        gameObject->objectRenderer->SetSpriteSheetIndex(frameIndex, animationName);
    }
};
