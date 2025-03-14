#pragma once
#include "Entity.h"

class PhysicalEntity : public Entity
{
	bool mGravity = false;

public:

	void SetGravity(bool targetState);
	bool IsGravityOn() { return mGravity; };
	void OnCollision(Entity* collidedWith) override;
};

