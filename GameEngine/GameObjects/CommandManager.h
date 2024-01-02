#pragma once
#include "Component.h"
#include "..\InputHandler.h"

class Player;

class CommandManager : public Component
{
    InputHandler* inputHandler1;
    InputHandler* inputHandler2;
    
public:
    GameObject* player1;
    GameObject* player2;
    
    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void End() override;
};
