#pragma once
#include "Condition.h"
#include "Player.h"

class PlayerCondition_IsJumping : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsMoving : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsTouchingGround : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_IsDeploy : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};