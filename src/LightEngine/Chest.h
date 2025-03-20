#pragma once
#include "Entity.h"

class Animation;

class Chest : public Entity
{
	Animation* mAnimation;
	sf::Texture mTexture;
		
};

