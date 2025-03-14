#include "PlayerCondition.h"

bool PlayerCondition_IsJumping::OnTest(Player* owner)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        owner->OnJump();
        return true;
    }

    return false;
}

bool PlayerCondition_IsMoving::OnTest(Player * owner)
{
    return owner->IsMoving();
}

bool PlayerCondition_IsTouchingGround::OnTest(Player* owner)
{
    return !owner->IsGravityOn();
}
