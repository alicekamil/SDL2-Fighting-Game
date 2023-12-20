#include "Collider.h"

#include <SDL_render.h>

#include "ObjectRenderer.h"
#include "Transform.h"
#include "../TextureLoader.h"

Collider::Collider()
{
    offset = std::make_shared<Vector>(0, 0);
    scale = std::make_shared<Vector>(1, 1);
}

void Collider::Awake()
{
    Component::Awake();

    objectRenderer->collider = this;
}

bool Collider::CollidesWith(Collider* other)
{
    return GetBounds().CollidesWith(other->GetBounds());
}

bool Collider::CollidesWith(Bounds other)
{
    return GetBounds().CollidesWith(other);
}

void Collider::DrawDebugBound(Window* window)
{
    Bounds bounds = GetBounds();
    VectorInt bottomLeftScreenSpace = transform->WorldToScreen(Vector(bounds.x, bounds.y)); 
    VectorInt topRightScreenSpace = transform->WorldToScreen(Vector(bounds.x + bounds.w, bounds.y + bounds.h)); 
    SDL_Point points[] = 
        {
        SDL_Point(bottomLeftScreenSpace.x, bottomLeftScreenSpace.y),
        SDL_Point(bottomLeftScreenSpace.x, topRightScreenSpace.y),
        SDL_Point(topRightScreenSpace.x, topRightScreenSpace.y),
        SDL_Point(topRightScreenSpace.x, bottomLeftScreenSpace.y),
        SDL_Point(bottomLeftScreenSpace.x, bottomLeftScreenSpace.y)
    };
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderDrawLines(window->renderer, points, 5);

    Bounds punchBounds = Bounds(transform->position->x - (objectRenderer->flipped ? 1.3f : 0), transform->position->y - 1.f, 1.3f, .5f);
    VectorInt pBottomLeftScreenSpace = transform->WorldToScreen(Vector(punchBounds.x, punchBounds.y)); 
    VectorInt pTopRightScreenSpace = transform->WorldToScreen(Vector(punchBounds.x + punchBounds.w, punchBounds.y + punchBounds.h)); 
    SDL_Point pPoints[] = 
        {
        SDL_Point(pBottomLeftScreenSpace.x, pBottomLeftScreenSpace.y),
        SDL_Point(pBottomLeftScreenSpace.x, pTopRightScreenSpace.y),
        SDL_Point(pTopRightScreenSpace.x, pTopRightScreenSpace.y),
        SDL_Point(pTopRightScreenSpace.x, pBottomLeftScreenSpace.y),
        SDL_Point(pBottomLeftScreenSpace.x, pBottomLeftScreenSpace.y)
    };
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderDrawLines(window->renderer, pPoints, 5);
}

Bounds Collider::GetBounds()
{
    return Bounds(
        (transform->position->x + offset->x) - transform->scale->x * scale->x / 2,
        (transform->position->y + offset->y) - transform->scale->y * scale->y / 2,
        transform->scale->x * scale->x,
        transform->scale->y * scale->y);
}
