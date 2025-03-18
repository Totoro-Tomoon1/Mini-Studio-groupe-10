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

void Player::OnInitialize()
{
	SetLife(20);
	SetTag(PlatFormerScene::Tag::PLAYER);
	SetRigidBody(true);
	SetGravity(true);
	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
	mShape.setTexture(mCurrentTexture);
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
	//std::cout << GetScene()->GetView().getCenter().x << std::endl;

	mShape.move(mDepl);

	mIsMoving = false;

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

	if (pCollideWith->IsTag(PlatFormerScene::Tag::GROUND))
	{
		if (face == 1 || face == 3)
			mGravitySpeed = 0.f;

		if (face == 2 || face == 4)
			mDepl = sf::Vector2f(0, 0);

		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Fallzone))
	{
		TakeDamage(GetHP());

		return;
	}

	if (imuuneProgresse < immuneTime)
	{
		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Damagezone))
	{
		std::cout << "Player take damage" << std::endl;
		TakeDamage(1);
		std::cout << "Current hp player : " << GetHP() << std::endl;
		imuuneProgresse = 0;

		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::ENEMY) || pCollideWith->IsTag(PlatFormerScene::Tag::ENEMY_BULLET))
	{
		TakeDamage(1.f);
		imuuneProgresse = 0;

		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::BOSS) || pCollideWith->IsTag(PlatFormerScene::Tag::BOSS_BULLET))
	{
		TakeDamage(3.f);
		imuuneProgresse = 0;

		return;
	}
}

//void Player::OnFixedUpdate(float deltaTime) //Update physique
//{
//	mIsMoving = false;
//
//	OnFall(deltaTime);
//
//	mShape.setPosition(sf::Vector2f(mShape.getPosition().x, mShape.getPosition().y + mGravitySpeed * deltaTime));
//}

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
	mDepl = sf::Vector2f(mPlayerParameters.mMinSpeed * deltaTime, 0);
}

void Player::MoveLeft(float deltaTime)
{
	mDepl = sf::Vector2f(-mPlayerParameters.mMinSpeed * deltaTime, 0);
}

void Player::OnFall(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime * 200.f;
}

void Player::OnJump()
{
	mGravitySpeed -= 300.f;
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

void Player::Input()
{
	float deltaTime = GetDeltaTime();

	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

	if (std::abs(stickX) < 10)
		stickX = 0;

	std::cout << 10 * stickX / 100 << std::endl;

	mDepl = sf::Vector2f(10 * stickX / 100, 0);

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
	}*/
}

void Player::ActivateInput()
{
	isInputActive = true;
}

void Player::DesactivateInput()
{
	isInputActive = false;
}

bool Player::GetIsInputActivate()
{
	return isInputActive;
}

void Player::ResetmDepl()
{
	mDepl = sf::Vector2f(0, 0);
}

void Player::ChangeStatic(bool stat)
{
	SetStatic(stat);
}
