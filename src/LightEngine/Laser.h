#pragma once
#include "Bullet.h"

class Laser : public Bullet
{
	float mLifeTime = 2.5f;
	float mProcess = 0.f;

	sf::Texture* mTexture;

protected:

	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
};