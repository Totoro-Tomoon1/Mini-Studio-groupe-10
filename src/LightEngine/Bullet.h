#pragma once
#include "Entity.h"
#include "PlatFormerScene.h"

class Bullet : public Entity
{
	sf::Texture* mTexture;
	bool isPlayer = false;

public:
	//void SetTag(int tag);
	void SetIsPlayer(bool isP) { isPlayer = isP; }

protected:

	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
	void OnFixedUpdate(float deltaTime	) override;
};