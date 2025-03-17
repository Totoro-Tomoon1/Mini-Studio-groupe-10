#pragma once
#include "PhysicalEntity.h"
#include "Life.h"
#include "Animations.h"

class Enemy : public PhysicalEntity, public Life
{
	Animation* mAnimation;
	sf::Texture* mCurrentTexture;

public:
	Enemy();

protected:
	void OnInitialize();
	void OnUpdate();
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;

};

