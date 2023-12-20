#include "GameObject.h"

#include "ObjectRenderer.h"
#include "Transform.h"
#include "../GameLogic.h"

GameObject::GameObject()
{
    Init();
    Start();
}

void GameObject::Init()
{
    transform = new Transform();
    objectRenderer = new ObjectRenderer();
    components = {};

    transform->Init(this);
    objectRenderer->Init(this);

    GameLogic::RegisterGameObject(this);

    transform->Awake();
    objectRenderer->Awake();
}

void GameObject::Start()
{
    transform->Start();
    objectRenderer->Start();
}

void GameObject::Update(float deltaTime)
{
    if(destroyed)
        return;
    
    transform->Update(deltaTime);
    objectRenderer->Update(deltaTime);
    for (Component* component : components)
    {
        component->Update(deltaTime);
        component->LateUpdate();
    }
}

void GameObject::FixedUpdate()
{
    if(destroyed)
        return;
    
    transform->FixedUpdate();
    objectRenderer->FixedUpdate();
    for (Component* component : components)
    {
        component->FixedUpdate();
    }
}

void GameObject::End()
{
    destroyed = true;
    GameLogic::UnregisterGameObject(this);
    
    transform->End();
    objectRenderer->End();

    const int componentCount = components.size();
    for (int i = componentCount - 1; i >= 0; --i)
    {
        RemoveComponent(components[i]);
    }

    delete transform;
    delete objectRenderer;
}
