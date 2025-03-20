#pragma once
#include "Entity.h"
#include "PlatFormerScene.h"

class Bullet : public Entity
{
public:
	void SetTag(int tag);

protected:

	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
	void OnFixedUpdate(float deltaTime	) override;
};