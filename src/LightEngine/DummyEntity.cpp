#include "DummyEntity.h"

#include <iostream>
#include "Utils.h"

void DummyEntity::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;

	AABBCollider c1 = GetAABBCollider();

	AABBCollider c2 = other->GetAABBCollider();

	int face = Utils::GetFace(c1, c2);

	std::cout << "Collide with face : " << face << std::endl;
}