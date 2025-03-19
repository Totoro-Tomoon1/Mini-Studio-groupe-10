#include "Enemy2.h"
#include "Utils.h"
#include "Bullet.h"
#include "AssetManager.h"

#define Mob2_Path "../../../res/MODELSHEET_MOB_VOLANT_ANIM_VOLE.png"

Enemy2::Enemy2()
{
}

void Enemy2::OnInitialize()
{
	SetLife(5.f);
	SetTag(PlatFormerScene::Tag::ENEMY);
	Enemy::OnInitialize();

	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(Mob2_Path);
	mAnimation = new Animation(Mob2_Path, sf::IntRect(0, 0, 125, 90), 8, true);
	mAnimation->SetStartSize(0, 15, 125, 90);
	mShape.setTexture(mCurrentTexture);
	mShape.setSize(sf::Vector2f(125 / 2, 90 / 2));
}

void Enemy2::OnUpdate()
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

void Enemy2::OnCollision(Entity* pCollideWith)
{
	Enemy::OnCollision(pCollideWith);

}

void Enemy2::OnFixedUpdate(float deltaTime)
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

void Enemy2::Shoot(float deltaTime)
{
	mLastAttackTime += deltaTime;

	if (mLastAttackTime > mAttackTimer)
	{
		mLastAttackTime = 0.f;

		sf::Vector2f dronePosition = mDroneTarget->GetPosition();
		sf::Vector2f myPosition = GetPosition();

		sf::Vector2f shotDirection = { dronePosition.x - myPosition.x, dronePosition.y - myPosition.y };

		Utils::Normalize(shotDirection);

		Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
		b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
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