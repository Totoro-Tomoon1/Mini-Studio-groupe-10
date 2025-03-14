#pragma once
#include "PhysicalEntity.h"
#include "Animations.h"
#include "StateMachine.h"

struct DroneParameter
{
	float mMinSpeed = 800.f;
	float mMaxSpeed = 400.f;
	float mAcceleration = 200.f;
	float mDeceleration = 200.f;
};

class Drone : public PhysicalEntity
{

	StateMachine<Drone> mStateMachine;

	enum State
	{
		Idle,
		Moving,
		Shooting,

		
		Count
	};
private:
	DroneParameter mDroneParameters;
	bool mIsMoving = false;
	bool mIsShooting = false;


	int mAreaIndex;
	sf::Vector2f* mDronePosition;
	Animation* mDroneAnimation;
	sf::Texture* mCurrentTexture;
	float mGravitySpeed = 0;

public:
	const char* GetStateName(State state) const;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	void Shoot(float deltaTime);
	bool IsMoving();
	bool IsShooting();

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;

	friend class DroneAction_Idle;
	friend class DroneAction_Moving;

};

