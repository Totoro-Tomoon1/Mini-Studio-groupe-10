#include "Drone.h"

void Drone::OnInitialize()
{

}

void Drone::OnUpdate()
{

}

void Drone::OnCollision(Entity* pCollideWith)
{

}

void Drone::OnFixedUpdate(float deltaTime)
{
	mIsMoving = false;

	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	bool A = sf::Joystick::isButtonPressed(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		MoveRight(deltaTime);
		mIsMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		MoveLeft(deltaTime);
		mIsMoving = true;
	}
}

void Drone::MoveRight(float deltaTime)
{
	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;

	mPlayerPosition.x += mPlayerParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x + mPlayerParameters.mMinSpeed * deltaTime, mShape.getPosition().y));*/
}

void Drone::MoveLeft(float deltaTime)
{

	//mSpeed += mAcceleration * deltaTime;
	//if (mSpeed > mMaxSpeed)
	//	mSpeed = mMaxSpeed;

	//mPlayerPosition.x -= mPlayerParameters.mMinSpeed * deltaTime;
	//mShape.setPosition(sf::Vector2f(mShape.getPosition().x - mPlayerParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}
