#include "Player.h"

// #include <complex>
// #include <iostream>

#include <algorithm>

#include "GameObject.h"
#include "ObjectRenderer.h"
#include "Transform.h"
#include "../Animator.h"
#include "../Math/Math.h"

class Animator;


void Player::Start()
{
    Component::Start();

    objectRenderer->SetSpriteSheet("img/AnimationSheet.png", 8, 10);
    transform->scale->x = 3;
    transform->scale->y = 3;
    Animator* animator = gameObject->GetComponent<Animator>();
    AddObserver(animator);
    Notify(*gameObject, StartIdle);

    collider = gameObject->AddComponent<Collider>();
    health = gameObject->AddComponent<Health>();
    attack = gameObject->AddComponent<Attack>();
    attack->player = this;

    //collider->debugLines = true;

    collider->scale->x = 0.3f;
    collider->scale->y = 0.7f;    
    collider->offset->y = -0.35f;    
}

void Player::FixedUpdate()
{
    Component::FixedUpdate();

    if(other->transform->position->x >= transform->position->x)
    {
        isLeftOfOther = true;
    }
    else
    {
        isLeftOfOther = false;
    }

    objectRenderer->flipped = isLeftOfOther ? false : true;

    if(isMoving && !locked)
        transform->position->x += (horizontalSpeed * speedMultiplier) * moveSpeed;

    if(isJumping)
    {
        UpdateJump();
    }
}

void Player::UpdateJump()
{
    currentTimeInAir += 0.016f * jumpSpeedMultiplier;

    float t = std::sin(currentTimeInAir * (PI / jumpDuration));
    if (currentTimeInAir < jumpDuration / 2.f)
    {
        transform->position->y = -6.f + t * jumpHeight;
    }
    else
    {
        if (!isFalling)
        {
            isFalling = true;
            Notify(*gameObject, Event::StartFall);
        }
        transform->position->y = -6.f + Math::EaseInSin(t) * jumpHeight;
    }

    if(currentTimeInAir >= jumpDuration)
    {
        currentTimeInAir = 0.f;
        isJumping = false;
        isFalling = false;
        transform->position->y = -6.f;
        speedMultiplier = 1.f;

        Move(0);
        Notify(*gameObject, Event::StartIdle);
    }
}

void Player::Move(float direction)
{
    if(locked || isCrouching)
    {
        horizontalSpeed = 0;
        isMoving = false;
        return;
    }

    if(isJumping) return;
    
    if(direction < 0 && horizontalSpeed > 0)
        horizontalSpeed = 0;
    
    float towards = direction - horizontalSpeed;
    towards = std::clamp(towards, -1.f, 1.f);
    
    horizontalSpeed += towards;

    if (std::abs(horizontalSpeed) < 0.1f && isMoving)
    {
        // player has stopped moving
        isMoving = false;
        
            Notify(*gameObject, StartIdle);
    }

    if (std::abs(horizontalSpeed) >= 0.1f && !isMoving)
    {
        // player has started moving
        isMoving = true;
        
            Notify(*gameObject, StartWalk);
    }
}

void Player::Crouch(bool isCrouching)
{
    if(locked || isJumping)
    {
        this->isCrouching = false;
        return;
    }
    
    this->isCrouching = isCrouching;
    if (isCrouching)
    {
        speedMultiplier = 0;
        Notify(*gameObject, StartCrouch);
    }
    else
    {
        speedMultiplier = 1;
        Notify(*gameObject, isMoving ? StartWalk : StartIdle);
    }
}

void Player::Jump()
{
    if(locked || isJumping)
        return;
    
    isJumping = true;
    speedMultiplier = 0.9f;
    Notify(*gameObject, Event::StartJump);
}

void Player::PauseJump()
{
    if(!isJumping)
        return;
    
    jumpSpeedMultiplier = 0.f;
}

void Player::ResumeJump()
{
    if(!isJumping)
        return;
    
    jumpSpeedMultiplier = 1.f;
    if(currentTimeInAir < jumpDuration / 2.f)
    {
        currentTimeInAir = jumpDuration - currentTimeInAir;
    }
}

