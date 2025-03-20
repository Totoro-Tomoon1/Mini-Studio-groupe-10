#pragma once
#include "Entity.h"

class Animation;

class Chest : public Entity
{
	Animation* mAnimation;
	sf::Texture mTexture;

	bool mHaveKey = false;

public:
	void OnOpen();

protected:
	void OnCollision(Entity* collidedWith) override;
		
};

