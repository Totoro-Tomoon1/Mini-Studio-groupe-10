#pragma once
#include "PhysicalEntity.h"
#include "Life.h"
#include "Animations.h"

class Enemy : public PhysicalEntity, public Life
{
	Animation* mAnimation;
	sf::Texture* mCurrentTexture;
	sf::Vector2f mDepl;

	float mChangeDirectionTimer = 4.f;
	float mChangeDirectionProcess = 0.f;

public:
	Enemy();

protected:
	void OnInitialize();
	void OnUpdate();
	void OnFixedUpdate(float deltaTime) override;

};

