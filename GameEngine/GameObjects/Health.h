#pragma once
#include "Component.h"
#include "../Events/Subject.h"

class Health : public Component, public Subject
{
    int currentHealth;
public:
    int initialHealth = 10;

    virtual void Start() override;
    void ChangeHealth(int delta);
};
