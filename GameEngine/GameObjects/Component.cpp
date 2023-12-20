#include "Component.h"

#include <cstdio>

#include "GameObject.h"

Component::Component()
{
    transform = nullptr;
    objectRenderer = nullptr;
}

void Component::Init(GameObject* gameObject)
{
    this->gameObject = gameObject;
    this->transform = gameObject->transform;
    this->objectRenderer = gameObject->objectRenderer;
}

void Component::Awake()
{
    
}

void Component::Start()
{
    
}

void Component::Update(float deltaTime)
{
    
}

void Component::FixedUpdate()
{
    
}

void Component::LateUpdate()
{
    
}

void Component::End()
{
    
}
