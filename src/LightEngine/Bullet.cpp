#include "Bullet.h"
#include "PlatFormerScene.h"
#include <iostream>
#include "AssetManager.h"

#define Bullet_Path "../../../res/MODEL_SHEET_FX_TIRE_MOB.png"

void Bullet::OnInitialize()
{
	mShape.setSize({ 48, 13 });
	mDirection = { 3.0f, 0.f };
	mSpeed = 1.f;

	mTexture = GameManager::Get()->GetAssetManager()->GetTexture(Bullet_Path);
	mShape.setTexture(mTexture);

	if (!isPlayer)
	{
		mShape.setTextureRect(sf::IntRect(302,26,48,13));
	}
	else
	{
		mShape.setTextureRect(sf::IntRect(302, 94, 48, 13));
	}
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

	if (GetPosition().x > right || GetPosition().x < left)
	{
		Destroy();
	}
}

void Bullet::OnFixedUpdate(float deltaTime)
{
	mShape.move(mDirection * mSpeed * deltaTime);
}