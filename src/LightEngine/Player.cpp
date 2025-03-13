#include "Player.h"
#include "PlatFormerScene.h"
#include "PlayerAction.h"
#include "PlayerCondition.h"
#include "Debug.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player() : mStateMachine(this, (int)State::Count)
{

}

void Player::OnInitialize()
{
	SetTag(PlatFormerScene::Tag::PLAYER);
	SetRigidBody(true);
	SetPosition(600.f, 400.f);
	mPlayerPosition = GetPosition();

	//Idle
	{
		PlayerAction_Idle* pIdle = mStateMachine.CreateAction<PlayerAction_Idle>(State::Idle);

		//-> Moving
		{
			auto transition = pIdle->CreateTransition(State::Moving);

			transition->AddCondition<PlayerCondition_IsMoving>();
		}

		//-> Jump
		{
			auto transition = pIdle->CreateTransition(State::Jump);

			transition->AddCondition<PlayerCondition_IsJumping>();
		}

		//-> Fall
		{
			auto transition = pIdle->CreateTransition(State::Fall);

			transition->AddCondition<PlayerCondition_IsTouchingGround>(false);
		}
	}

	//Moving
	{
		PlayerAction_Moving* pMoving = mStateMachine.CreateAction<PlayerAction_Moving>(State::Moving);

		//-> Idle
		{
			auto transition = pMoving->CreateTransition(State::Idle);

			transition->AddCondition<PlayerCondition_IsMoving>(false);
		}

		//-> Jump
		{
			auto transition = pMoving->CreateTransition(State::Jump);

			transition->AddCondition<PlayerCondition_IsJumping>();
		}

		//-> Fall
		{
			auto transition = pMoving->CreateTransition(State::Fall);

			transition->AddCondition<PlayerCondition_IsTouchingGround>(false);
		}
	}

	//Jump	
	{
		PlayerAction_Jump* pJumping = mStateMachine.CreateAction<PlayerAction_Jump>(State::Jump);

		//-> Fall
		{
			auto transition = pJumping->CreateTransition(State::Fall);

			transition->AddCondition<PlayerCondition_IsJumping>();
			transition->AddCondition<PlayerCondition_IsTouchingGround>(false);
		}
	}

	//Fall
	{
		PlayerAction_Fall* pFalling = mStateMachine.CreateAction<PlayerAction_Fall>(State::Fall);

		//-> Idle
		{
			auto transition = pFalling->CreateTransition(State::Idle);

			transition->AddCondition<PlayerCondition_IsTouchingGround>();
		}
	}

	mStateMachine.SetState(State::Idle);
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{
	mStateMachine.Update();
	Debug::DrawText(0, 0, std::to_string(mPlayerParameters.mMinSpeed), sf::Color::White);
	Debug::DrawText(GetPosition().x + 50.f, GetPosition().y + 50.f, GetStateName((Player::State)mStateMachine.GetCurrentState()), sf::Color::Red);
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
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

	/*if (stickX < 0)
		MoveLeft(deltaTime);

	if (stickX > 0)
		MoveRight(deltaTime);*/

	/*if (A == true)
	{
		OnJump(deltaTime);
	}*/

	if (IsGravityOn()) //C'est un test du fall
	{
		OnFall(deltaTime);
	}

	//Update de la position en fonction de si y'a eu Jump ou Fall
	mPlayerPosition.y += mGravitySpeed * deltaTime;
	SetPosition(mPlayerPosition.x, mPlayerPosition.y);
}

//Pour l'affichage debug
const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Moving: return "Moving";
	case Jump: return "Jump";
	case Fall: return "Fall";
	default: return "Unknown";
	}
}

void Player::OnCollision(Entity* pCollideWith)
{
	if (pCollideWith->IsTag(PlatFormerScene::Tag::GROUND))
	{
		SetGravity(false);
		mGravitySpeed = 0.f;
	}
}

void Player::MoveRight(float deltaTime)
{
	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

	mPlayerPosition.x += mPlayerParameters.mMinSpeed * deltaTime;
}

void Player::MoveLeft(float deltaTime)
{
	
	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

	mPlayerPosition.x -= mPlayerParameters.mMinSpeed * deltaTime;
}

void Player::OnFall(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime * 200.f;
}

void Player::OnJump()
{
	mGravitySpeed -= 500.f;
	SetGravity(true);
}

bool Player::IsMoving()
{
	return mIsMoving;
}
