#pragma once
#include "Entity.h"
#include "Animations.h"
#include "StateMachine.h"
#include "Life.h"

struct DroneParameter
{
	float mMinSpeed = 600.f;
	float mMaxSpeed = 200.f;
	float mAcceleration = 200.f;
	float mDeceleration = 200.f;
};

class Drone : public Entity, public Life
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

	bool hasKey = false;

	sf::Vector2f* mDronePosition;
	Animation* mDroneAnimation;
	sf::Texture* mCurrentTexture;

	sf::Vector2f mDepl;

	bool isInputActive = false;
	bool isUnlocked = false;
	float immuneTime = 1.f;
	float imuuneProgresse = 0.f;

public:
	Drone();

	const char* GetStateName(State state) const;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	bool IsMoving();
	bool CanHack();
	void Shoot(float deltaTime);

	void Input();
	void Undisplay();
	void Display(sf::Vector2f posPlayer);

	void ActivateInput();
	void DesactivateInput();

	bool GetIsInputActivate();
	void ResetmDepl();

	bool GetIsUnlocked();
	void ChangeIsUnlocked();

	bool HaseKey() { return hasKey; }

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


