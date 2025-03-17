#include "Player.h"
#include "PlatFormerScene.h"
#include "PlayerAction.h"
#include "PlayerCondition.h"
#include "Debug.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

Player::Player() : mStateMachine(this, (int)State::Count)
{
	mDepl = sf::Vector2f(0, 0);
}


//void Player::SetPosition(float x, float y, float ratioX, float ratioY)
//{
//	Entity::SetPosition(x, y, ratioX, ratioY);
//	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
//	mShape->setTexture(mCurrentTexture);
//}

void Player::OnInitialize()
{
	SetLife(20);
	SetTag(PlatFormerScene::Tag::PLAYER);
	SetRigidBody(true);
	SetGravity(true);
	//SetPosition(600.f, 400.f);
	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
	mShape.setTexture(mCurrentTexture);
	//mPlayerAnimation = new Animation(PLAYER_PATH, sf::IntRect(0, 0, 160, 130), 6, false); //� modifier
	mPlayerAnimation = new Animation(PLAYER_PATH, sf::IntRect(0,0,123,100), 8, true);
	mPlayerAnimation->SetStartSize(0, 0, 123, 100);

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
	if (GetHP() <= 0)
	{
		std::cout << "You're dead" << std::endl;
	}

	imuuneProgresse += GetDeltaTime();

	mPlayerAnimation->Update(GetDeltaTime());
	mShape.setTextureRect(*mPlayerAnimation->GetTextureRect());

	mStateMachine.Update();
	Debug::DrawText(0, 0, std::to_string(mPlayerParameters.mMinSpeed), sf::Color::White);
	Debug::DrawText(GetPosition().x + 50.f, GetPosition().y + 50.f, GetStateName((Player::State)mStateMachine.GetCurrentState()), sf::Color::Red);
}

void Player::OnCollision(Entity* pCollideWith)
{
	AABBCollider c1 = GetAABBCollider();

	AABBCollider c2 = pCollideWith->GetAABBCollider();

	int face = Utils::GetFace(c1, c2);

	

	//std::cout << "Collide with face : " << face << std::endl;

	if (pCollideWith->IsTag(PlatFormerScene::Tag::GROUND))
	{
		//SetGravity(false);
		if (face == 1 || face == 3)
			mGravitySpeed = 0.f;

		if (face == 2 || face == 4)
			mDepl = sf::Vector2f(0, 0);
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Damagezone) && imuuneProgresse >= immuneTime)
	{
		std::cout << "Player take damage" << std::endl;
		TakeDamage(1);
		std::cout << "Current hp player : " << GetHP() << std::endl;
		imuuneProgresse = 0;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Fallzone))
	{
		TakeDamage(GetHP());
	}
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

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		MoveLeft(deltaTime);
		mIsMoving = true;
	}

	else
	{
		mDepl = sf::Vector2f(0, 0);
	}

	/*if (stickX < 0)
		MoveLeft(deltaTime);

	if (stickX > 0)
		MoveRight(deltaTime);*/

	/*if (A == true)
	{
		OnJump(deltaTime);
	}*/

	OnFall(deltaTime);

	//Update de la position en fonction de si y'a eu Jump ou Fall
	//mPlayerPosition.y += mGravitySpeed * deltaTime;
	mShape.move(mDepl);
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x, mShape.getPosition().y + mGravitySpeed * deltaTime));
	//SetPosition(mPlayerPosition.x, mPlayerPosition.y);
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

void Player::MoveRight(float deltaTime)
{
	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

	//mPlayerPosition.x += mPlayerParameters.mMinSpeed * deltaTime;
	//mShape.setPosition(sf::Vector2f(mShape.getPosition().x + mPlayerParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
	mDepl = sf::Vector2f(mPlayerParameters.mMinSpeed * deltaTime, 0);
}

void Player::MoveLeft(float deltaTime)
{
	
	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

	//mPlayerPosition.x -= mPlayerParameters.mMinSpeed * deltaTime;
	//mShape.setPosition(sf::Vector2f(mShape.getPosition().x - mPlayerParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
	mDepl = sf::Vector2f(-mPlayerParameters.mMinSpeed * deltaTime, 0);
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

float Player::GetGravitySpeed()
{
	return mGravitySpeed;
}

sf::Vector2f* Player::GetDepl()
{
	return &mDepl;
}
