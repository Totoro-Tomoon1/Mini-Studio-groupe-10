#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
protected:
	float mAttackProcess = 0.f;
	float mAttackTimerBoss = 3.5f;
	
	sf::Texture* mTexture;
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