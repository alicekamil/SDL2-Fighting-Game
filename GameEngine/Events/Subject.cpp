#include "Subject.h"

void Subject::Notify(const GameObject& gameObject, Event event)
{
    for (int i = 0; i < observers.size(); i++)
    {
        observers[i]->OnNotify(gameObject, event);
    }
}

void Subject::AddObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
