#pragma once

#include "PlayerCondition.h"
#include "PlayerAction.h"
#include "PhysicalEntity.h"
#include "StateMachine.h"

struct PlayerParameter
{
	float mMinSpeed = 50.f;
	float mMaxSpeed = 100.f;
	float mAcceleration = 25.f;
	float mDeceleration = 75.f;
};

class Player : public PhysicalEntity
{
public:

	StateMachine<Player> mStateMachine;

	enum State
	{
		Idle,
		Moving,
		Jump,
		Fall,

		Count
	};

private:

	float mAcceleration = 50.f;
	float mSpeed = 50.f;
	float mMaxSpeed = 500.f;
	
	float mDeceleration;

	float mFallDuration = 1.0f;

	float mJumpDuration = 1.0f;

	int mAreaIndex;
	sf::Vector2f mPlayerPosition;
	float mGravitySpeed = 0;

public:
	Player();
	
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void OnFall(float deltaTime);
	void OnJump(float deltaTime);

	friend class PlayerAction_Idle;
	friend class PlayerAction_Moving;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Fall;
};

