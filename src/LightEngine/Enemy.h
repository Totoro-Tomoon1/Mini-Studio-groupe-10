#pragma once
#include "PhysicalEntity.h"
#include "Life.h"
#include "Animations.h"
#include "Drone.h"
	
class Enemy : public PhysicalEntity, public Life
{
protected:

	Animation* mAnimation;
	sf::Texture* mCurrentTexture;
	sf::Vector2f mDepl;
	Drone* mDroneTarget = nullptr;
	bool mIsAttacking = false;
	float mChangeDirectionTimer = 4.f;
	float mChangeDirectionProcess = 0.f;
	bool reverse = false;

	float mAttackTimer = 1.f;
	float mLastAttackTime = 0.f;

public:
	Enemy();

	void SetDroneTarget(Drone* drone);
	void SetTextureAndAnim(const char* path);
protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;

};