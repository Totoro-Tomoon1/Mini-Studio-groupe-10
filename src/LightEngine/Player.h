#pragma once
#include "PhysicalEntity.h"
#include "Animations.h"

class Player : public PhysicalEntity
{
	sf::Shape* mShape;
	sf::Vector2f mPlayerPosition;
	Animation* mPlayerAnimation;
	sf::Texture* mCurrentTexture;
	float mGravitySpeed = 0;

public:
	void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override;

	void OnInitialize() override;
	void OnUpdate() override;
	void OnFixedUpdate(float deltaTime) override;
	void Fall(float deltaTime);
	void Jump(float deltaTime);

};

