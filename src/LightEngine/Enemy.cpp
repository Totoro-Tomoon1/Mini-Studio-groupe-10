#include "Enemy.h"
#include "PlatFormerScene.h"

Enemy::Enemy()
{
}

void Enemy::OnInitialize()
{
	SetLife(20.f);
	SetTag(PlatFormerScene::Tag::ENEMY);
	SetRigidBody(true);
	SetGravity(true);
	mDepl = { 1.f, 0.f };
	SetSpeed(1.f);
}

void Enemy::OnUpdate()
{
}

void Enemy::OnFixedUpdate(float deltaTime)
{
	mChangeDirectionProcess += deltaTime;
	
	if (mChangeDirectionProcess > mChangeDirectionTimer)
	{
		mDepl = -mDepl;
		mChangeDirectionProcess = 0.f;
	}

	mShape.move(mDepl * mSpeed);
}
