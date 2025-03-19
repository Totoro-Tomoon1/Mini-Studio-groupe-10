#pragma once
#include "Entity.h"

class PhysicalEntity : public Entity
{
protected:

	bool mGravity = false;
	float mGravitySpeed = 0;

public:

	void SetGravity(bool targetState);
	bool IsGravityOn() { return mGravity; };
	void OnCollision(Entity* collidedWith) override;
	void OnFixedUpdate(float deltaTime) override;
};