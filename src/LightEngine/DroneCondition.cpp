#include "DroneCondition.h"

bool DroneCondition_IsMoving::OnTest(Drone* owner)
{
	return owner->IsMoving();
}

bool DroneCondition_IsShooting::OnTest(Drone* owner)
{
	if (sf::Joystick::isButtonPressed(0, 7) && owner->GetIsInputActivate())
	{
		return true;
	}

	return false;
}

bool DroneCondition_TryHacking::OnTest(Drone* owner)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		return true;
	}

	return false;
}

bool DroneCondition_CanHack::OnTest(Drone* owner)
{
	return owner->CanHack();
}