#pragma once
#include <vector>

#include "Component.h"

class GameObject
{
    friend class GameLogic;

    bool destroyed = false;

    GameObject();

    void Init();
    void Start();
    void Update(float deltaTime);
    void FixedUpdate();
    void End();

    std::vector<Component*> components;
public:
    Transform* transform;
    ObjectRenderer* objectRenderer;

    template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>>* = nullptr>
    T* AddComponent();
    template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>>* = nullptr>
    T* GetComponent();
    template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>>* = nullptr>
    void RemoveComponent(T* component);
};

template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>>*>
T* GameObject::AddComponent()
{
    T* component = new T();
    components.push_back(component);

    component->Init(this);
    component->Awake();
    component->Start();
    
    return component;
}

template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>>*>
T* GameObject::GetComponent()
{
    for (auto component : components)
    {
        if(typeid(*component) == typeid(T))
            return static_cast<T*>(component);
    }

    return nullptr;
}

template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>>*>
void GameObject::RemoveComponent(T* component)
{
    // remove if it contains
    if(std::ranges::find(components, component) != components.end())
    {
        std::erase(components, component);
        component->End();
        delete component;
    }
}
