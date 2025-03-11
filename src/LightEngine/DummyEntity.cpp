#include "DummyEntity.h"

#include <iostream>
#include "Utils.h"

void DummyEntity::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;

	AABBCollider c1;
	c1.xMin = GetPosition().x ;
	c1.xMax = GetPosition().x + GetSize().x;
	c1.yMin = GetPosition().y;
	c1.yMax = GetPosition().y + GetSize().y;

	AABBCollider c2;
	c2.xMin = other->GetPosition().x ;
	c2.xMax = other->GetPosition().x + other->GetSize().x;
	c2.yMin = other->GetPosition().y;
	c2.yMax = other->GetPosition().y + other->GetSize().y;

	int face = Utils::GetFace(c1, c2);

	std::cout << "Collide with face : " << face << std::endl;
}