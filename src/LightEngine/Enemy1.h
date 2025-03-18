#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy
{

public:
	Enemy1();

	void Shoot(float deltaTime);

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
};

