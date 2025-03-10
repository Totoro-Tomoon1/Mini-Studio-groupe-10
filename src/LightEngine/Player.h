#pragma once
#include "PhysicalEntity.h"

class Player : public PhysicalEntity
{
	sf::Vector2f mPlayerPosition;
	float mGravitySpeed = 0;

public:

	void OnInitialize() override;
	void OnUpdate() override;
	void OnFixedUpdate(float deltaTime) override;
	void Fall(float deltaTime);
	void Jump(float deltaTime);
};

