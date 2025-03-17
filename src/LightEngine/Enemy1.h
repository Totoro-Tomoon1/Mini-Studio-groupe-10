#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy
{

public:
	Enemy1();

protected:
	void OnInitialize();
	void OnUpdate();
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
};

