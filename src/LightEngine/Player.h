#pragma once
#include "PhysicalEntity.h"
#include "Animations.h"
#include "StateMachine.h"
#include "Life.h"

struct PlayerParameter
{
	float mPlayerSpeed = 800.f;
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

	
	sf::Texture* mCurrentTexture;
	

	sf::Vector2f mDepl;

	float immuneTime = 1.f;
	float immuneProgress = 0.f;

	bool isInputActive = false;
	bool haseKey = false;

	bool reverse = false;
public:
	Player();
	
	const char* GetStateName(State state) const;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
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

	Animation* mPlayerAnimation;

	friend class PlayerAction_Idle;
	friend class PlayerAction_Moving;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Fall;
};