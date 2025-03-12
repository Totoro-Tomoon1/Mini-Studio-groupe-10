#include "Player.h"
#include "Scene.h"
#include "Debug.h"

Player::Player() : mStateMachine(this, (int)State::Count)
{

}

void Player::OnInitialize()
{
	SetRigidBody(true);
	SetPosition(0.f, 400.f);
	mPlayerPosition = GetPosition();

	//Idle
	{
		PlayerAction_Idle* pIdle = mStateMachine.CreateAction<PlayerAction_Idle>(State::Idle);

		//-> Moving
		{
			auto transition = pIdle->CreateTransition(State::Moving);

			//ici ajouter la condition
		}

		//-> Jump
		{
			auto transition = pIdle->CreateTransition(State::Jump);

			//Ici add condition
		}
	}

	//Moving
	{
		PlayerAction_Moving* pMoving = mStateMachine.CreateAction<PlayerAction_Moving>(State::Moving);

		//-> Idle
		{
			auto transition = pMoving->CreateTransition(State::Idle);

			//ici ajouter la condition
		}

		//-> Jump
		{
			auto transition = pMoving->CreateTransition(State::Jump);

			//Ici add condition
		}

		//-> Fall
		{
			auto transition = pMoving->CreateTransition(State::Fall);

			//Ici add condition
		}
	}

	//Jump	
	{
		PlayerAction_Jump* pJumping = mStateMachine.CreateAction<PlayerAction_Jump>(State::Jump);

		//-> Fall
		{
			auto transition = pJumping->CreateTransition(State::Fall);

			//Ici add condition
		}
	}

	//Fall
	{
		PlayerAction_Fall* pFalling = mStateMachine.CreateAction<PlayerAction_Fall>(State::Jump);

		//-> Idle
		{
			auto transition = pFalling->CreateTransition(State::Idle);

			//Ici add condition
		}
	}

	mStateMachine.SetState(State::Idle);
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{
	Debug::DrawText(0, 0, std::to_string(mSpeed), sf::Color::White);
}

void Player::OnCollision(Entity* pCollideWith)
{
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
{
	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	bool A = sf::Joystick::isButtonPressed(0, 0);

	//Tests sans manette
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		MoveRight(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		MoveLeft(deltaTime);

	/*if (stickX < 0)
		MoveLeft(deltaTime);

	if (stickX > 0)
		MoveRight(deltaTime);*/

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
