#include "Player.h"

void Player::OnInitialize()
{
	SetPosition(500.f, 500.f);
	mPlayerPosition = GetPosition();
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
{
	if (IsGravityOn()) //C'est un test du fall
	{
		Fall(deltaTime);
	}

	//Update de la position en fonction de si y'a eu Jump ou Fall
	mPlayerPosition.y += mGravitySpeed * deltaTime;

	SetPosition(mPlayerPosition.x, mPlayerPosition.y);
}

void Player::Fall(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime;
	
}

void Player::Jump(float deltaTime)
{
	mGravitySpeed -= 10.f;
}
