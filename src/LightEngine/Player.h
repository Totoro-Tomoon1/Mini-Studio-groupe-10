#pragma once
#include "PhysicalEntity.h"
#include "Animations.h"
#include "StateMachine.h"
#include "Life.h"

struct PlayerParameter
{
	float mMinSpeed = 800.f;
	float mMaxSpeed = 200.f;
	float mAcceleration = 200.f;
	float mDeceleration = 200.f;
};

class Player : public PhysicalEntity, public Life
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

	PlayerParameter mPlayerParameters;
	bool mIsMoving = false;

	int mAreaIndex;
	sf::Vector2f* mPlayerPosition;
	Animation* mPlayerAnimation;
	sf::Texture* mCurrentTexture;
	float mGravitySpeed = 0;

	sf::Vector2f mDepl;

	float immuneTime = 1.f;
	float imuuneProgresse = 0.f;

	bool isInputActive = false;

public:
	Player();
	
	const char* GetStateName(State state) const;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void OnFall(float deltaTime);
	void OnJump();
	bool IsMoving();

	float GetGravitySpeed();
	sf::Vector2f* GetDepl();

	void Input();
	void ActivateInput();
	void DesactivateInput();

	bool GetIsInputActivate();
	void ResetmDepl();

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

