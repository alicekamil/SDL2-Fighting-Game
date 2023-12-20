#pragma once
#include <memory>

#include "Component.h"
#include "../Window.h"
#include "../Math/Bounds.h"

class Vector;

class Collider : public Component
{
public:
    Collider();

    Uint8 r = 255, g = 0, b = 0;
    
    bool debugLines = false;
    std::shared_ptr<Vector> offset;
    std::shared_ptr<Vector> scale;

    virtual void Awake() override;

    bool CollidesWith(Collider* other); 
    bool CollidesWith(Bounds other); 
    void DrawDebugBound(Window* window);
    
    virtual Bounds GetBounds();
};
