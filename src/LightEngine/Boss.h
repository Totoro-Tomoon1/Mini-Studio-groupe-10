#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
	bool mIsMovable;

public:
	Boss();

	void Shoot(float deltaTime);
	void Rush(float deltaTime);

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
};

