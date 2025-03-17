#include "Enemy1.h"
#include "Utils.h"
#include "Bullet.h"

Enemy1::Enemy1()
{
}

void Enemy1::OnInitialize()
{
	Enemy::OnInitialize();

	//Setter les textures ici
}

void Enemy1::OnUpdate()
{
	Enemy::OnUpdate();

	sf::Vector2f dronePos = mDroneTarget->GetPosition();

	float distance = Utils::GetDistance(dronePos.x, dronePos.y, mShape.getPosition().x, mShape.getPosition().y);

	if (distance < 500.f)
		mIsAttacking = true;
	else
		mIsAttacking = false;
}

void Enemy1::OnCollision(Entity* pCollideWith)
{

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

		sf::Vector2f dronePosition = mDroneTarget->GetPosition();
		sf::Vector2f myPosition = GetPosition();

		mShotDirection = { dronePosition.x - myPosition.x, dronePosition.y - myPosition.y };

		Utils::Normalize(mShotDirection);

		Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
		b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
		b->SetDirection(mShotDirection.x, mShotDirection.y);
	}
}