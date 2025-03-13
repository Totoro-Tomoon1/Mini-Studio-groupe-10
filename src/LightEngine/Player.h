#pragma once

#include "PhysicalEntity.h"
#include "StateMachine.h"

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

	//float mAcceleration = 50.f;
	//float mSpeed = 200.f;
	//float mMaxSpeed = 800.f;

	float mSpeed = 800.f;

	bool mIsMoving = false;

	sf::Vector2f mPlayerPosition;
	float mGravitySpeed = 0.f;

public:
	Player();
	
	const char* GetStateName(State state) const;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void OnFall(float deltaTime);
	void OnJump();
	bool IsMoving();

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

