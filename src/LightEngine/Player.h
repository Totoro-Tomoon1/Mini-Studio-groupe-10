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
		Deploy,

		Count
	};

private:

	PlayerParameter mPlayerParameters;
	bool mIsMoving = false;

	Animation* mPlayerAnimation;
	sf::Texture* mCurrentTexture;
	

	sf::Vector2f mDepl;

	float immuneTime = 1.f;
	float imuuneProgresse = 0.f;

	bool isInputActive = false;
	bool haseKey = false;

public:
	Player();
	
	const char* GetStateName(State state) const;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void OnFall(float deltaTime);
	void IsDeploy();
	void OnJump();
	bool IsMoving();

	float GetGravitySpeed();
	sf::Vector2f* GetDepl();

	void Input();
	void ActivateInput();
	void DesactivateInput();

	bool GetIsInputActivate();
	void ResetmDepl();

	void ChangeStatic(bool stat);
	bool HaseKey();

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	//void OnFixedUpdate(float deltaTime) override;

	friend class PlayerAction_Idle;
	friend class PlayerAction_Moving;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Fall;
};