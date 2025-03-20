#include "Enemy.h"
#include "PlatFormerScene.h"
#include "AssetManager.h"

Enemy::Enemy()
{
}

void Enemy::SetDroneTarget(Drone* drone)
{
	mDroneTarget = drone;
}

void Enemy::OnInitialize()
{
	
	SetRigidBody(true);
	mDepl = { 1.f, 0.f };
	SetSpeed(100.f);
}

void Enemy::OnUpdate()
{
	if (GetHP() <= 0.f)
	{
		Destroy();
		return;
	}

	mChangeDirectionProcess += GameManager::Get()->GetDeltaTime();

	if (mChangeDirectionProcess > mChangeDirectionTimer)
	{
		mDepl = -mDepl;
		mChangeDirectionProcess = 0.f;
	}

	
}

void Enemy::OnCollision(Entity* pCollideWith)
{
	if (pCollideWith->IsTag(PlatFormerScene::Tag::PLAYER_BULLET))
		TakeDamage(1.f);

	if (pCollideWith->IsTag(PlatFormerScene::Tag::GROUND))
		mGravitySpeed = 0.f;
}

void Enemy::OnFixedUpdate(float deltaTime)
{
	mShape.move(mDepl * mSpeed * deltaTime);

	if (IsGravityOn())
		PhysicalEntity::OnFixedUpdate(deltaTime);
}
