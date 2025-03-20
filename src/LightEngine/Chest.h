#pragma once
#include "Entity.h"
#include "Drone.h"

class Animation;

class Chest : public Entity
{
	Animation* mAnimation;
	sf::Texture mTexture;


public:
	void OnOpen();
	
};

