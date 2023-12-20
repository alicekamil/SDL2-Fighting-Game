#include "Attack.h"
#include "Player.h"
#include "Transform.h"
#include "../Animator.h"

void Attack::Start()
{
    Component::Start();

    AddObserver(gameObject->GetComponent<Animator>());
}

void Attack::Update(float deltaTime)
{
    Component::Update(deltaTime);

    if(punchStarted && punchHitBoxEnabled && !hasHitEnemy)
    {
        Bounds punchBound = GetPunchBounds();
        if(player->other->collider->CollidesWith(punchBound))
        {
            player->other->health->ChangeHealth(-punchDamage);
            hasHitEnemy = true;
        }
    }
}

void Attack::StartPunch()
{
    if(punchStarted || player->locked) return;

    player->PauseJump();
    player->locked = true;
    punchStarted = true;
    Notify(*gameObject, Event::StartPunch);
}

void Attack::EnablePunchHitBox()
{
    if(punchStarted)
        punchHitBoxEnabled = true;
}

void Attack::DisablePunchHitBox()
{
    if(punchStarted)
        punchHitBoxEnabled = false;
}

void Attack::EndPunch()
{
    punchStarted = false;
    punchHitBoxEnabled = false;
    hasHitEnemy = false;

    player->locked = false;
    Notify(*gameObject, Event::StartIdle);

    player->ResumeJump();
}

Bounds Attack::GetPunchBounds()
{
    float offset = 0;

    if(!player->isLeftOfOther)
    {
        offset = -punchWidth;
    }
    
    return Bounds(transform->position->x + offset, transform->position->y - punchHeight * 2, punchWidth, punchHeight);
}
