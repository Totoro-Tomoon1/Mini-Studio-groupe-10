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
