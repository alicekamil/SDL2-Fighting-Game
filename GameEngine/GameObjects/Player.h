#pragma once
#include "Attack.h"
#include "Collider.h"
#include "Health.h"
#include "Component.h"
#include "../Events/Subject.h"

class Player : public Component, Subject
{
    float horizontalSpeed = 0;
    float speedMultiplier = 1;
    float jumpSpeedMultiplier = 1;
    bool isMoving;
    bool isCrouching;
    bool isFalling;
    bool isJumping;

    float currentTimeInAir;

    void UpdateJump();
    
public:
    Player* other;
    Collider* collider;
    Attack* attack;
    Health* health;

    bool locked;
    float moveSpeed = 0.1f;
    float jumpDuration = 0.8f;
    float jumpHeight = 3.3f;
    bool isLeftOfOther;

    
    virtual void Start() override;
    virtual void FixedUpdate() override;
    
    void Move(float direction);
    void Crouch(bool isCrouching);
    void Jump();
    void PauseJump();
    void ResumeJump();
};
