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
	sf::Vector2f mShotDirection;
	Drone* mDroneTarget;
	bool mIsAttacking = false;
	float mChangeDirectionTimer = 4.f;
	float mChangeDirectionProcess = 0.f;

public:
	Enemy();

	void SetDroneTarget(Drone* drone);
protected:
	void OnInitialize();
	void OnUpdate();
	void OnFixedUpdate(float deltaTime) override;

};

