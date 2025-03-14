#include "DroneCondition.h"

bool DroneCondition_IsMoving::OnTest(Drone* owner)
{
    return owner->IsMoving();
}

bool DroneCondition_IsShooting::OnTest(Drone* owner)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        owner->IsShooting();
        return true;
    }

    return false;
}