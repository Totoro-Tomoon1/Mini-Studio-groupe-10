#pragma once

#include "Enemy.h"

class GroundEnemy : public Enemy
{
	Animation* mAnimation;
	sf::Texture* mCurrentTexture;
	sf::Vector2f mDepl;

	float mChangeDirectionTimer = 4.f;
	float mChangeDirectionProcess = 0.f;

public:
	GroundEnemy();

protected:
	void OnInitialize() override;
    void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;

};

