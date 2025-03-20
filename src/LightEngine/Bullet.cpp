#include "Bullet.h"
#include "PlatFormerScene.h"
#include <iostream>

void Bullet::OnInitialize()
{
	
	mDirection = { 3.0f, 0.f };
	mSpeed = 1.f;
}

void Bullet::OnCollision(Entity* other)
{
	if (other->IsTag(PlatFormerScene::Tag::GROUND))
	{
		Destroy();
		return;
	}

	if (IsTag(PlatFormerScene::Tag::PLAYER_BULLET))
	{
		if (other->IsTag(PlatFormerScene::Tag::ENEMY) || other->IsTag(PlatFormerScene::Tag::BOSS))
		{
			Destroy();
			return;
		}
	}
	else
	{
		if (other->IsTag(PlatFormerScene::Tag::PLAYER) || other->IsTag(PlatFormerScene::Tag::DRONE))
		{
			Destroy();
			return;
		}
	}
	
}

void Bullet::OnUpdate()
{
	mShape.move(mDirection);

	float left = GetScene()->GetView().getCenter().x - GetScene()->GetWindowWidth() / 2;

	float right = GetScene()->GetView().getCenter().x + GetScene()->GetWindowWidth() / 2;

	//std::cout << "Bullet x : " << GetPosition().x << "    right : " << right << std::endl;

	if (GetPosition().x > right || GetPosition().x < left)
	{
		std::cout << "Destroy" << std::endl;
		Destroy();
	}
}

void Bullet::OnFixedUpdate(float deltaTime)
{
	mShape.move(mDirection * mSpeed * deltaTime);
}

void Bullet::SetTag(int tag)
{
	Entity::SetTag(tag);
}