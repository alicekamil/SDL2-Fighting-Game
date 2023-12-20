#include "Animator.h"
#include<iostream>
#include "GameObjects/Player.h"
#include "GameObjects/Attack.h"

Animator::Animator()
{
    currentAnimationTime = 0.0f;

    std::function<void(GameObject*)> enableAttack = [](GameObject* gameObject)
    {
        gameObject->GetComponent<Attack>()->EnablePunchHitBox();
    };
    std::function<void(GameObject*)> disableAttack = [](GameObject* gameObject)
    {
        gameObject->GetComponent<Attack>()->DisablePunchHitBox();
    };
    std::function<void(GameObject*)> endAttack = [](GameObject* gameObject)
    {
        gameObject->GetComponent<Attack>()->EndPunch();
    };

    std::function<void(GameObject*)> lock = [](GameObject* gameObject)
    {
        gameObject->GetComponent<Player>()->locked = true;
    };
    std::function<void(GameObject*)> startIdle = [](GameObject* gameObject)
    {
        gameObject->GetComponent<Player>()->locked = false;
        gameObject->GetComponent<Animator>()->OnNotify(*gameObject, StartIdle);
    };

    Animation* idleAnimation = new Animation{Idle, 1, 1, false, {Keyframe{0.0f, 0}}};

    Animation* walkAnimation = new Animation{
        Walk, 8, 0.8f, true,
        {
            Keyframe{0.0f, 0},
            Keyframe{0.1f, 1},
            Keyframe{0.2f, 2},
            Keyframe{0.3f, 3},
            Keyframe{0.4f, 4},
            Keyframe{0.5f, 5},
            Keyframe{0.6f, 6},
            Keyframe{0.7f, 7}
        }
    };

    Animation* crouchAnimation = new Animation{Crouch, 1, 1, false, {Keyframe{0.0f, 0}}};

    Animation* punchAnimation = new Animation{
        Punch, 7, 0.9f, false,
        {
            Keyframe{0.0f, 0},
            Keyframe(0.1f, 1),
            Keyframe(0.2f, 2),
            Keyframe(0.3f, 3),
            Keyframe(0.4f, 4, enableAttack),
            Keyframe(0.5f, 5),
            Keyframe(0.6f, 6, disableAttack),
            Keyframe(0.7f, 7),
            Keyframe(0.9f, 7, endAttack)
        }
    };

    Animation* hurtAnimation = new Animation{
        Hurt, 4, 0.4f, false,
        {
            Keyframe{0.0f, 0, lock},
            Keyframe{0.1f, 1},
            Keyframe{0.2f, 2},
            Keyframe{0.3f, 3, startIdle},
            Keyframe{0.3f, 3, endAttack}
        }
    };

    Animation* deathAnimation = new Animation{
        Death, 6, 0.8f, false,
        {
            Keyframe{0.0f, 0, lock},
            Keyframe{0.1f, 1},
            Keyframe{0.2f, 2},
            Keyframe{0.3f, 3},
            Keyframe{0.4f, 4},
            Keyframe{0.7f, 5}
        }
    };

    Animation* jumpAnimation = new Animation{
        Jump, 3, 0.5f, false,
        {
            Keyframe{0.0f, 1},
            Keyframe{0.1f, 2}
        }
    };

    Animation* fallAnimation = new Animation{
        Fall, 2, 0.2f, true,
        {
            Keyframe{0.0f, 0},
            Keyframe{0.1f, 1}
        }
    };

    Animation* airAttackAnimation = new Animation{
        AirAttack, 4, 0.7f, false,
        {
            Keyframe{0.0f, 0},
            Keyframe{0.2f, 1},
            Keyframe{0.3f, 2},
            Keyframe{0.5f, 3},
            Keyframe{0.6f, 0}
        }
    };

    Animation* crouchAttackAnimation = new Animation{
        CrouchAttack, 4, 0.7f, false,
        {
            Keyframe{0.0f, 0},
            Keyframe{0.1f, 1},
            Keyframe{0.3f, 2},
            Keyframe{0.5f, 3},
            Keyframe{0.6f, 0, endAttack}
        }
    };

    animations[Idle] = idleAnimation;
    animations[Walk] = walkAnimation;
    animations[Crouch] = crouchAnimation;
    animations[Punch] = punchAnimation;
    animations[Hurt] = hurtAnimation;
    animations[Death] = deathAnimation;
    animations[Jump] = jumpAnimation;
    animations[Fall] = fallAnimation;
    animations[AirAttack] = airAttackAnimation;
    animations[CrouchAttack] = crouchAttackAnimation;
}

Animator::~Animator()
{
    std::map<AnimationName, Animation>::iterator it;

    for (auto const& animation : animations)
    {
        std::cout << animation.first  // AnimationName key
                  << ':' 
                  << animation.second // Value (type of Animation) 
                  << std::endl;

        delete animation.second;
    }
    animations.clear();
}

void Animator::OnNotify(const GameObject& gameObject, Event event)
{
    currentAnimationTime = 0.0f;
    switch (event)
    {
    case StartWalk:
        currentAnimation = animations[Walk];
        break;
    case StartIdle:
        currentAnimation = animations[Idle];
        break;
    case StartCrouch:
        currentAnimation = animations[Crouch];
        break;
    case StartPunch:
        currentAnimation = animations[Punch];
        break;
    case StartHurt:
        currentAnimation = animations[Hurt];
        break;
    case StartDeath:
        currentAnimation = animations[Death];
        break;
    case StartJump:
        currentAnimation = animations[Jump];
        break;
    case StartFall:
        currentAnimation = animations[Fall];
        break;
    case StartAirAttack:
        currentAnimation = animations[AirAttack];
        break;
    case StartCrouchAttack:
        currentAnimation = animations[CrouchAttack];        
        break;
    }
}

void Animator::Update(float deltaTime)
{
    Component::Update(deltaTime);
    if (currentAnimation == NULL)
    {
        return;
    }

    for (int i = 0; i <= currentAnimation->keyframes.size() - 1; i++)
    {
        auto keyframe = currentAnimation->keyframes[i];

        if (i == currentAnimation->keyframes.size() - 1)
        {
            if (currentAnimationTime >= keyframe.time)
            {
                keyframe.Execute(gameObject, currentAnimation->animationName);
            }

            if (currentAnimationTime >= currentAnimation->length && currentAnimation->shouldLoop)
            {
                currentAnimationTime -= currentAnimation->length;
            }
            break;
        }

        if (currentAnimationTime >= keyframe.time && currentAnimationTime < currentAnimation->keyframes[i + 1].time)
        {
            keyframe.Execute(gameObject, currentAnimation->animationName);
        }
    }
    currentAnimationTime += deltaTime;
}
