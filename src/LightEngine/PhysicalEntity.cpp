#include "PhysicalEntity.h"
#include <iostream>

void PhysicalEntity::SetGravity(bool targetState)
{
	mGravity = targetState;
}

void PhysicalEntity::OnCollision(Entity* collidedWith)
{
	//std::cout << "test" << std::endl;
}

void PhysicalEntity::OnFixedUpdate(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime * 200.f;

	mShape.setPosition(sf::Vector2f(mShape.getPosition().x, mShape.getPosition().y + mGravitySpeed * deltaTime));
}
