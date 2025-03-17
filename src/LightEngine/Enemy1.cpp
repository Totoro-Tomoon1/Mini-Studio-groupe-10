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

	float distance = Utils::GetDistance(dronePos.x, dronePos.y, mTarget.position.x, mTarget.position.y);

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
		sf::Vector2f direction = mDroneTarget->GetPosition();
		Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
		b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
		//b->SetDirection(direction.x, direction.y);
	}
	else
	{
		Enemy::OnFixedUpdate(deltaTime);
	}
}
