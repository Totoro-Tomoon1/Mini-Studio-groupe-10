#pragma once
#include "Entity.h"
#include "PlatFormerScene.h"

class Bullet : public Entity
{
public:

	void OnInitialize() override;
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
	void SetTag(int tag);
};