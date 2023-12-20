#include "Health.h"

#include "Player.h"
#include "../Animator.h"
#include "../GameLogic.h"

void Health::Start()
{
    Component::Start();
    AddObserver(gameObject->GetComponent<Animator>());
    currentHealth = initialHealth;
}

void Health::ChangeHealth(int delta)
{
    currentHealth += delta;

    if(delta < 0 && currentHealth > 0)
    {
        Notify(*gameObject, StartHurt);
    }
    
    if(currentHealth <= 0)
    {
        Notify(*gameObject, StartDeath);
    }
}
