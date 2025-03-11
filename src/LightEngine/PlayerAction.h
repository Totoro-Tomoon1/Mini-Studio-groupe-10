#pragma once

#include "Action.h"
#include "Player.h"


class PlayerAction_Idle : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override {}
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Jump : public Action<Player>
{
	float mJumpTimer = 0.0f;

public:
	void OnStart(Player* pPlayer) override {}
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Fall : public Action<Player>
{
	float mFallTImer = 0.0f;
public:
	void OnStart(Player* pPlayer) override {}
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

