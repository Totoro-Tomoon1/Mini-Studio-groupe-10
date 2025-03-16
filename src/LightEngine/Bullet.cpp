#include "Bullet.h"
#include "PlatFormerScene.h"

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

	if (GetPosition().x > GetScene()->GetWindowWidth()) //à modifier
	{
		Destroy();
	}
}