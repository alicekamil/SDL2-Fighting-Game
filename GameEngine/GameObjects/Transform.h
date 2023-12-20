#pragma once
#include <memory>

#include "Component.h"
#include "../Math/Vector.h"
#include "../Math/VectorInt.h"

class Transform : public Component
{
    const float WidthBound = 15.f;
public:
    Transform();
    std::shared_ptr<Vector> position;
    std::shared_ptr<Vector> scale;

    virtual void End() override;

    VectorInt WorldToScreenPos();
    VectorInt WorldToScreenScale();
    VectorInt WorldToScreen(Vector position);
};
