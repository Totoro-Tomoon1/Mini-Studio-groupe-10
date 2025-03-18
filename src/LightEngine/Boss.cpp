#include "Boss.h"
#include "Utils.h"
#include "Bullet.h"

Boss::Boss()
{
}

void Boss::OnInitialize()
{
	SetLife(5.f);
	SetTag(PlatFormerScene::Tag::BOSS);

	Enemy::OnInitialize();

	//Setter les textures ici
}

void Boss::OnUpdate()
{
	Enemy::OnUpdate();

	if (mDroneTarget == nullptr)
		return;

	sf::Vector2f dronePos = mDroneTarget->GetPosition();

	float distance = Utils::GetDistance(dronePos.x, dronePos.y, mShape.getPosition().x, mShape.getPosition().y);

	if (distance < 500.f)
		mIsAttacking = true;
	else
		mIsAttacking = false;
}

void Boss::OnCollision(Entity* pCollideWith)
{
	Enemy::OnCollision(pCollideWith);
}

void Boss::OnFixedUpdate(float deltaTime)
{
	if (mIsAttacking)
	{
		Shoot(deltaTime);
		Punch(deltaTime);
	}
	else
	{
		Enemy::OnFixedUpdate(deltaTime);
	}
}

void Boss::Shoot(float deltaTime)
{
	mLastAttackTime += deltaTime;

	if (mLastAttackTime > mAttackTimerBoss)
	{
		sf::Vector2f dronePosition = mDroneTarget->GetPosition();
		sf::Vector2f myPosition = GetPosition();

		sf::Vector2f shotDirection = { dronePosition.x - myPosition.x, dronePosition.y - myPosition.y };

		Utils::Normalize(shotDirection);

		Bullet* b = CreateEntity<Bullet>(sf::Vector2f(50.f, 10.f), sf::Color::Yellow);
		b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
		b->SetDirection(shotDirection.x, shotDirection.y);
		b->SetRigidBody(false);
		b->SetTag(PlatFormerScene::Tag::BOSS_BULLET);
	}

}

void Boss::Punch(float deltaTime)
{
	mLastAttackTime += deltaTime;

	if (mLastAttackTime > mPunchAttackTime)
	{
		mLastAttackTime = 0.f;

		sf::Vector2f dronePosition = mDroneTarget->GetPosition();
		sf::Vector2f myPosition = GetPosition();

		GoToDirection(dronePosition.x, dronePosition.y, 70);
		

	}

}
