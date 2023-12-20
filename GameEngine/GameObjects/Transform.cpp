#include "Transform.h"

#include <cmath>

#include "../Window.h"
#include "../Math/Math.h"

Transform::Transform()
{
    position = std::make_shared<Vector>(0, 0);
    scale = std::make_shared<Vector>(1, 1);
}

void Transform::End()
{
    Component::End();
}

VectorInt Transform::WorldToScreenPos()
{
    float heightToWidthRatio = static_cast<float>(Window::ScreenHeight) / static_cast<float>(Window::ScreenWidth);
    float heightBound = WidthBound * heightToWidthRatio;

    int screenX = Math::Lerp(0, Window::ScreenWidth, Math::InverseLerp(-WidthBound, WidthBound, position->x));
    int screenY = Math::Lerp(0, Window::ScreenHeight, Math::InverseLerp(-heightBound, heightBound, -position->y));
    return VectorInt(screenX, screenY);
}

VectorInt Transform::WorldToScreenScale()
{
    const float cellSize = static_cast<float>(Window::ScreenWidth) / (WidthBound * 2.f);
    float x = cellSize * scale->x;
    float y = cellSize * scale->y;

    return VectorInt(static_cast<int>(x), static_cast<int>(y));
}

VectorInt Transform::WorldToScreen(Vector position)
{
    float heightToWidthRatio = static_cast<float>(Window::ScreenHeight) / static_cast<float>(Window::ScreenWidth);
    float heightBound = WidthBound * heightToWidthRatio;

    int screenX = Math::Lerp(0, Window::ScreenWidth, Math::InverseLerp(-WidthBound, WidthBound, position.x));
    int screenY = Math::Lerp(0, Window::ScreenHeight, Math::InverseLerp(-heightBound, heightBound, -position.y));
    return VectorInt(screenX, screenY);
}
