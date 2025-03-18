#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
protected:
	float mPunchAttackTime = 1.f;
	float mAttackTimerBoss = 1.f;
	

public:
	Boss();

	void Shoot(float deltaTime);
	void Punch(float deltaTime);

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
};

