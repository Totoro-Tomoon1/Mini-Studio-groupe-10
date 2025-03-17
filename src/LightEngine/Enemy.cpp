#include "Enemy.h"
#include "PlatFormerScene.h"

Enemy::Enemy()
{
}

void Enemy::SetDroneTarget(Drone* drone)
{
	mDroneTarget = drone;
}

void Enemy::OnInitialize()
{
	SetLife(1.f);
	SetTag(PlatFormerScene::Tag::ENEMY);
	SetRigidBody(true);
	SetGravity(true);
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
}

void Enemy::OnFixedUpdate(float deltaTime)
{
	mShape.move(mDepl * mSpeed * deltaTime);
}
