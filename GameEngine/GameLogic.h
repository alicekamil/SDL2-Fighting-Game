#pragma once
#include "GameObjects/GameObject.h"

class Vector;

class GameLogic
{
public:
    inline static std::vector<GameObject*> GameObjects;

    GameLogic();
    
    void Init();
    void Update(float deltaTime);
    void FixedUpdate();
    void End();

    static GameObject* Instantiate();
    static GameObject* Instantiate(Vector& position);
    static GameObject* Instantiate(Vector& position, Vector& scale);
    static void Destroy(GameObject* gameObject);
    static void RegisterGameObject(GameObject* gameObject);
    static void UnregisterGameObject(GameObject* gameObject);
};
