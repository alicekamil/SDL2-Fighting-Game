#pragma once
#include <map>

#include "Animation.h"
#include "Events/Observer.h"

class Animator : public Component, public Observer 
{
private:
    std::map<AnimationName ,Animation*> animations; 

    float currentAnimationTime;
    
public:
    Animator();
    ~Animator() override;
    Animation* currentAnimation;
    void OnNotify(const GameObject& gameObject, Event event) override;
    void Update(float deltaTime) override;
};
