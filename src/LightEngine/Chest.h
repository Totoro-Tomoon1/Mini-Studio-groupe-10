#pragma once
#include "Entity.h"


class Animation;

class Chest : public Entity
{
private:

	Animation* mAnimation;
	sf::Texture* mTexture;


public:
	void OnOpen();
protected:
	void OnCollision(Entity* pCollideWith) override;
	void OnInitialize() override;
	
};

