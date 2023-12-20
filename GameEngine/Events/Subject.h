#pragma once
#include <vector>

#include "Observer.h"
#include "../Event.h"
#include "../GameObjects/Component.h"

class Subject
{
private:
    std::vector<Observer*> observers;

protected:
    void Notify(const GameObject& gameObject, Event event);
    
public:
    void AddObserver(Observer* observer);

    void RemoveObserver(Observer* observer);
    
};
