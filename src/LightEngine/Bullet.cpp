#include "Bullet.h"
#include "PlatFormerScene.h"
#include <iostream>

void Bullet::OnInitialize()
{
	mDirection = { 3.f, 0.f };
}

void Bullet::OnCollision(Entity* other)
{
	if (other->IsTag(PlatFormerScene::Tag::GROUND))
	{
		Destroy();
	}
}

void Bullet::OnUpdate()
{
	mShape.move(mDirection);

	float left = GetScene()->GetView().getCenter().x - GetScene()->GetWindowWidth() / 2;

	float right = GetScene()->GetView().getCenter().x + GetScene()->GetWindowWidth() / 2;

	//std::cout << "Bullet x : " << GetPosition().x << "    right : " << right << std::endl;

	if (GetPosition().x > right || GetPosition().x < left) //à modifier
	{
		std::cout << "Destroy" << std::endl;
		Destroy();
	}
}