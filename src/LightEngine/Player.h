#pragma once

#include "PhysicalEntity.h"
#include "Animations.h"
#include "StateMachine.h"

struct PlayerParameter
{
	float mMinSpeed = 800.f;
	float mMaxSpeed = 200.f;
	float mAcceleration = 200.f;
	float mDeceleration = 200.f;
};

class Player : public PhysicalEntity
{
public:
	void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override;

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

	sf::Shape* mShape;
	sf::Vector2f mPlayerPosition;
	Animation* mPlayerAnimation;
	sf::Texture* mCurrentTexture;
	float mGravitySpeed = 0;
	PlayerParameter mPlayerParameters;
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

