#pragma once
#include "Entity.h"
#include "Animations.h"
#include "StateMachine.h"

struct DroneParameter
{
	float mMinSpeed = 600.f;
	float mMaxSpeed = 200.f;
	float mAcceleration = 200.f;
	float mDeceleration = 200.f;
};

class Drone : public Entity
{
public:

	StateMachine<Drone> mStateMachine;

	enum State
	{
		Idle,
		Moving,
		Shooting,
		Hacking,

		Count
	};

private:

	DroneParameter mDroneParameters;
	bool mIsMoving = false;
	bool mIsShooting = false;
	bool mCanHack = false;

	sf::Vector2f* mDronePosition;
	Animation* mDroneAnimation;
	sf::Texture* mCurrentTexture;

public:
	Drone();

	const char* GetStateName(State state) const;
	//void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override; //?

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	bool IsMoving();
	bool CanHack();
	void Shoot(float deltaTime);

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;

	friend class PlayerAction_Idle;
	friend class PlayerAction_Moving;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Fall;
};


