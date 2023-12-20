#pragma once
#include "../Event.h"
#include "../GameObjects/GameObject.h"


class Observer
{
public:
    virtual ~Observer() = default; 
    virtual void OnNotify(const GameObject&, Event event) {};
};
