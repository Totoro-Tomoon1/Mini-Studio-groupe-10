#pragma once
#include "Enemy.h"

class Animation;

class Enemy1 : public Enemy
{
	int bulletSpeed = 10;

public:
	Enemy1();

	void Shoot(float deltaTime);

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
};