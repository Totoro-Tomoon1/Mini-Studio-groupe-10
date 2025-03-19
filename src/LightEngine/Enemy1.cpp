#include "Enemy1.h"
#include "Utils.h"
#include "Bullet.h"
#include "AssetManager.h"
#include "Animations.h"

#include <iostream>

#define Mob1_Path "../../../res/MODELSHEET_MOB_TERRESTRE_MARCHE.png"

Enemy1::Enemy1()
{
}

void Enemy1::OnInitialize()
{
	SetLife(5.f);
	SetTag(PlatFormerScene::Tag::ENEMY);
	Enemy::OnInitialize();

	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(Mob1_Path);
	mAnimation = new Animation(Mob1_Path, sf::IntRect(0,0,195,220), 6, false);
	mAnimation->SetStartSize(0, 30, 195, 220);
	mShape.setTexture(mCurrentTexture);
	mShape.setSize(sf::Vector2f(195/2, 220/2));

}

void Enemy1::OnUpdate()
{
	Enemy::OnUpdate();

	if (mDroneTarget == nullptr)
	{
		SetDroneTarget(GetScene<PlatFormerScene>()->GetDrone());
		return;
	}

	sf::Vector2f dronePos = mDroneTarget->GetPosition();

	float distance = Utils::GetDistance(dronePos.x, dronePos.y, mShape.getPosition().x, mShape.getPosition().y);

	if (abs(distance) < 500.f)
		mIsAttacking = true;
	else
		mIsAttacking = false;

	mAnimation->Update(GetDeltaTime());
	mShape.setTextureRect(*mAnimation->GetTextureRect());

	if (reverse)
	{
		mShape.setScale(sf::Vector2f(-1, 1));
	}
	else
	{
		mShape.setScale(sf::Vector2f(1, 1));
	}
}

void Enemy1::OnCollision(Entity* pCollideWith)
{
	Enemy::OnCollision(pCollideWith);
}

void Enemy1::OnFixedUpdate(float deltaTime)
{
	if (mIsAttacking)
	{
		Shoot(deltaTime);
	}
	else
	{
		Enemy::OnFixedUpdate(deltaTime);
	}
}

void Enemy1::Shoot(float deltaTime)
{
	mLastAttackTime += deltaTime;

	if (mLastAttackTime > mAttackTimer)
	{
		mLastAttackTime = 0.f;

		sf::Vector2f dronePosition = mDroneTarget->GetPosition(0.5f, 0.5f);
		sf::Vector2f myPosition = GetPosition(0.5f, 0.5f);

		sf::Vector2f shotDirection = { dronePosition.x - myPosition.x, dronePosition.y - myPosition.y };

		//Utils::Normalize(shotDirection);

		Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
		b->SetPosition(myPosition.x, myPosition.y);
		float shootX = shotDirection.x;
		float shootY = shotDirection.y;
		float dist = sqrt((shootX * shootX) + (shootY * shootY));

		if (dist != bulletSpeed)
		{
			float vect = bulletSpeed / dist;

			shootX *= vect;
			shootY *= vect;
		}


		b->SetDirection(shootX, shootY);
		b->SetTag(PlatFormerScene::Tag::ENEMY_BULLET);
	}
}