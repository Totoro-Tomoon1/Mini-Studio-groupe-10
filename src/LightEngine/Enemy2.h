#pragma once
#include "Enemy.h"

class Enemy2 : public Enemy
{
	int bulletSpeed = 10;
public:
	Enemy2();

	void Shoot(float deltaTime);

protected:
	void OnInitialize() override;
    void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
};