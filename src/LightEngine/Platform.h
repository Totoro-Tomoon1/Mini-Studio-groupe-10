#pragma once
#include "Entity.h"

class Animation;

class Platform : public Entity
{
	sf::Texture* mTexture;

public:
	void OnInitialize() override;
	void SetTexture(int type);
	void OnUpdate() override;
	virtual void OnCollision(Entity* other) override;
};