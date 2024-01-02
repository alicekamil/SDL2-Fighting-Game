#pragma once

#include <map>
#include <SDL_stdinc.h>

#include "GameObjects/Attack.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/InputScheme.h"
#include "GameObjects/Player.h"
#include "GameObjects/Transform.h"


class Command
{
public:
    virtual ~Command() {}
    virtual void Execute(GameObject* character) = 0;
};

class Move : public Command 
{
    
    float direction;
    
public:
    Move(float direction) : direction(direction)
    {        
    }
    
    void Execute(GameObject* gameObject)
    {
        auto player = gameObject->GetComponent<Player>();
        player->Move(direction);
    }
};

class Punch : public Command
{
    void Execute(GameObject* gameObject)
    {
        gameObject->GetComponent<Attack>()->StartPunch();
    }
};

class Jump : public Command
{
    void Execute(GameObject* gameObject)
    {
        auto player = gameObject->GetComponent<Player>();
        player->Jump();
    }
};

class Crouch : public Command
{
    bool isCrouching;
public:
    Crouch(bool isCrouching) : isCrouching(isCrouching)
    {
        
    }
    void Execute(GameObject* gameObject)
    {
        gameObject->GetComponent<Player>()->Crouch(isCrouching);
    }
};

class InputHandler
{    
    Command* buttonLeftHold;
    Command* buttonRightHold;
    Command* buttonUpPress;
    Command* buttonDownPress;
    Command* buttonLeftRelease;
    Command* buttonRightRelease;
    Command* buttonUpRelease;
    Command* buttonDownRelease;
    Command* buttonPunchPress;

    InputScheme* inputScheme;

    std::map<int, bool> previousKeyState;
    
    //std::map <int, Command*> commands;
    //std::array<Command*, MAX_ACTION_INDEX> commands; //c++11 array
    
public:
    std::vector<Command*> HandleInput();
    InputHandler(InputScheme* inputScheme);
    ~InputHandler();
    
    //void bind(int key, CommandPtr command);
};

