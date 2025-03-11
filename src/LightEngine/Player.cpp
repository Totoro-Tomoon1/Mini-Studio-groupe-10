#include "Player.h"
#include "Scene.h"
#include "Debug.h"

Player::Player() : mStateMachine(this, State::Count)
{

}

void Player::OnInitialize()
{
	mPlayerPosition = GetPosition();
	SetGravity(true);
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{

}

void Player::OnCollision(Entity* pCollideWith)
{
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
{
	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	bool A = sf::Joystick::isButtonPressed(0, 0);

	if (stickX < 0)
		MoveLeft(deltaTime);

	if (stickX > 0)
		MoveRight(deltaTime);

	if (A == true)
	{
		OnJump(deltaTime);
	}

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

	mPlayerPosition.x += 100.f * deltaTime;
	mPlayerPosition.x += mSpeed * deltaTime;
}

void Player::MoveLeft(float deltaTime)
{
	
	mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;

	mPlayerPosition.x -= 100.f * deltaTime;
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
