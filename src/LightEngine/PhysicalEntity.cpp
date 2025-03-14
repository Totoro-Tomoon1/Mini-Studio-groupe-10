#include "PhysicalEntity.h"

void PhysicalEntity::SetGravity(bool targetState)
{
	mGravity = targetState;
}

void PhysicalEntity::OnCollision(Entity* collidedWith)
{

}
