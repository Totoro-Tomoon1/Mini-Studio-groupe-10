#include "Boss.h"
#include "Utils.h"
#include "Laser.h"

Boss::Boss()
{
}

void Boss::OnInitialize()
{
	SetLife(5.f);
	SetTag(PlatFormerScene::Tag::BOSS);
	mAttackTimer = 3.5f;
	mLastAttackTime = 0.f;
	Enemy::OnInitialize();

	//Setter les textures ici
}

void Boss::OnUpdate()
{
	Enemy::OnUpdate();

	mLastAttackTime += GameManager::Get()->GetDeltaTime();

	if(mLastAttackTime > 2.5f)
		mIsMovable = true;

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
}

void Boss::OnCollision(Entity* pCollideWith)
{
	Enemy::OnCollision(pCollideWith);

	if (pCollideWith->IsTag(PlatFormerScene::Tag::BOSS_BULLET))
	{
		mIsMovable = false;
	}
}

void Boss::OnFixedUpdate(float deltaTime)
{
	if (mIsAttacking)
	{
		if (mLastAttackTime > mAttackTimer)
		{
			mLastAttackTime = 0.f;
			Shoot(deltaTime);
		}

		if (mIsMovable)
		{
			Rush(deltaTime);
		}
	}
	else
	{
		Enemy::OnFixedUpdate(deltaTime);
	}
}

void Boss::Shoot(float deltaTime)
{
		sf::Vector2f dronePosition = mDroneTarget->GetPosition(0.5f, 0.5f);
		sf::Vector2f myPosition = GetPosition(0.5f, 0.5f);

		sf::Vector2f shotDirection = { dronePosition.x - myPosition.x, dronePosition.y - myPosition.y };

		Utils::Normalize(shotDirection);

		float deltaX = 0.f;

		if (dronePosition.x - myPosition.x < 0)
		{
			deltaX = 700.f;
		}

		Laser* b = CreateEntity<Laser>(sf::Vector2f(700.f, 50.f), sf::Color::Yellow);
		b->SetPosition(myPosition.x - deltaX, myPosition.y);
		b->SetTag(PlatFormerScene::Tag::BOSS_BULLET);
}

void Boss::Rush(float deltaTime)
{
	sf::Vector2f dronePosition = mDroneTarget->GetPosition();
	sf::Vector2f myPosition = GetPosition();

	mDepl = { dronePosition.x - myPosition.x, dronePosition.y - myPosition.y };
	
	Utils::Normalize(mDepl);

	mShape.move(mDepl * mSpeed * deltaTime);
}
