#include "Bullet.h"
#include "PlatFormerScene.h"

void Bullet::OnInitialize()
{
	mDirection = { 3.0f, 0.f };
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
		if (other->IsTag(PlatFormerScene::Tag::ENEMY))
		{
			Destroy();
			return;
		}
	}
	else
	{
		if (other->IsTag(PlatFormerScene::Tag::PLAYER))
		{
			Destroy();
			return;
		}
	}
	
}

void Bullet::OnUpdate()
{
	mShape.move(mDirection);

	if (GetPosition().x > GetScene()->GetWindowWidth()) //à modifier
	{
		Destroy();
	}
}

void Bullet::SetTag(int tag)
{
	Entity::SetTag(tag);
}
