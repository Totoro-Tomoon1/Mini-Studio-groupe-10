#pragma once
#include "Condition.h"
#include "Player.h"

class PlayerCondition_IsJumping : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};


