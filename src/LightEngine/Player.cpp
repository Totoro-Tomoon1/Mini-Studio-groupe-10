#include "Player.h"
#include "Scene.h"
#include "Debug.h"

Player::Player() : mStateMachine(this, State::Count)
{

}

void Player::OnInitialize()
{
	SetPosition(500.f, 500.f);
	mPlayerPosition = GetPosition();
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{
}

void Player::OnCollision(Entity* pCollideWith)
{
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
{
	if (IsGravityOn()) //C'est un test du fall
	{
		OnFall(deltaTime);
	}

	//Update de la position en fonction de si y'a eu Jump ou Fall
	mPlayerPosition.y += mGravitySpeed * deltaTime;

	SetPosition(mPlayerPosition.x, mPlayerPosition.y);
}

void Player::MoveRight(float deltaTime)
{
	mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;
	
	mPlayerPosition.x += mSpeed * deltaTime;
}

void Player::MoveLeft(float deltaTime)
{
	
	mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;

	mPlayerPosition.x -= mSpeed * deltaTime;
}

void Player::OnFall(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime;
	
}

void Player::OnJump(float deltaTime)
{
	mGravitySpeed -= 10.f;
}
