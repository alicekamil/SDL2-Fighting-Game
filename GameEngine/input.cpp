#include "input.h"
#
#include <SDL_keyboard.h>
#include <SDL_stdinc.h>

using namespace std;

InputHandler::InputHandler(InputScheme* inputScheme)
{

    this->inputScheme = inputScheme; //&inputScheme turns into ptr , inputScheme& then its reference?
        
    buttonLeftHold = new Move(-1.f);
    buttonLeftRelease = new Move(0);
    buttonRightHold = new Move(1.f);
    buttonRightRelease = new Move(0);
    buttonUpPress = new Jump();
    buttonDownPress = new Crouch(true);
    buttonDownRelease = new Crouch(false);
    buttonPunchPress = new Punch();
    previousKeyState = {};
}

InputHandler::~InputHandler()
{
    delete buttonLeftHold;
    delete buttonLeftRelease;
    delete buttonRightHold;
    delete buttonRightRelease;
    delete buttonUpPress;
    delete buttonUpRelease;
    delete buttonDownPress;
    delete buttonDownRelease;
    delete buttonPunchPress;

    delete inputScheme;
}

 std::vector<Command*> InputHandler::handleInput()
{
    std::vector<Command*> commands = { };
    
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[inputScheme->left] && previousKeyState[inputScheme->left]) commands.push_back(buttonLeftHold);
    if (!keystate[inputScheme->left] && previousKeyState[inputScheme->left]) commands.push_back(buttonLeftRelease);
    
    if (keystate[inputScheme->right] && previousKeyState[inputScheme->right]) commands.push_back(buttonRightHold);
    if (!keystate[inputScheme->right] && previousKeyState[inputScheme->right]) commands.push_back(buttonRightRelease);
    
    if (keystate[inputScheme->up] && !previousKeyState[inputScheme->up]) commands.push_back(buttonUpPress);
    //if (!keystate[inputScheme->up] && previousKeyState[inputScheme->up]) commands.push_back(buttonUpRelease);
    
    if (keystate[inputScheme->down] && !previousKeyState[inputScheme->down]) commands.push_back(buttonDownPress);
    if (!keystate[inputScheme->down] && previousKeyState[inputScheme->down]) commands.push_back(buttonDownRelease);

    if (keystate[inputScheme->punch] && !previousKeyState[inputScheme->punch]) commands.push_back(buttonPunchPress);

    previousKeyState[inputScheme->left] = keystate[inputScheme->left] == 1;
    previousKeyState[inputScheme->right] = keystate[inputScheme->right] == 1;
    previousKeyState[inputScheme->up] = keystate[inputScheme->up] == 1;
    previousKeyState[inputScheme->down] = keystate[inputScheme->down] == 1;
    previousKeyState[inputScheme->punch] = keystate[inputScheme->punch] == 1;    
    
    return commands;
    
};


