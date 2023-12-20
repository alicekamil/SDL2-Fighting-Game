#include "CommandManager.h"

#include <SDL_scancode.h>

#include "Player.h"
#include "../input.h"

void CommandManager::Start()
{
    Component::Start();

    inputHandler1 = new InputHandler(new InputScheme(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_E));
    inputHandler2 = new InputHandler(new InputScheme(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_KP_1));
}

void CommandManager::Update(float deltaTime)
{
    Component::Update(deltaTime);

    std::vector<Command*> commandsForPlayer1 = inputHandler1->handleInput();
    for (auto command : commandsForPlayer1)
    {
        command->execute(player1);
    }
    std::vector<Command*> commandsForPlayer2 = inputHandler2->handleInput();
    for (auto command : commandsForPlayer2)
    {
        command->execute(player2);
    }
}

void CommandManager::End()
{
    Component::End();

    delete inputHandler1;
    delete inputHandler2;
}
