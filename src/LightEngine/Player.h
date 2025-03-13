#pragma once
#include "PhysicalEntity.h"
#include "Animations.h"
#include "StateMachine.h"

class Player : public PhysicalEntity
{

	StateMachine<Player> mStateMachine;

	enum State
	{
		Idle,
		Jump,
		Fall,

		Count
	};

	float mAcceleration = 50.f;
	float mSpeed = 200.f;
	float mMaxSpeed = 800.f;
	
	float mDeceleration;

	float mFallDuration = 1.0f;

	float mJumpDuration = 1.0f;

	int mAreaIndex;
	sf::Shape* mShape;
	sf::Vector2f mPlayerPosition;
	Animation* mPlayerAnimation;
	sf::Texture* mCurrentTexture;
	float mGravitySpeed = 0;

public:
	Player();
	
	void SetAreaIndex(int index) { mAreaIndex = index; }
	const char* GetStateName(State state) const;
	//void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override; //?

protected:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* pCollideWith) override;
	void OnFixedUpdate(float deltaTime) override;
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void OnFall(float deltaTime);
	void OnJump(float deltaTime);

};

