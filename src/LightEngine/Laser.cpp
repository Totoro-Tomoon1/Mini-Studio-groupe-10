#include "Laser.h"

void Laser::OnInitialize()
{
	mDirection = { 0.f, 0.f };
}

void Laser::OnCollision(Entity* other)
{
}

void Laser::OnUpdate()
{
	mProcess += GameManager::Get()->GetDeltaTime();

	if (mProcess > mLifeTime)
		Destroy();
}