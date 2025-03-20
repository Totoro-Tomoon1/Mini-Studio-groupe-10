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
	
}

void Player::OnInitialize()
{
	SetLife(20);
	SetTag(PlatFormerScene::Tag::PLAYER);
	SetRigidBody(true);
	SetGravity(true);
	mDepl = sf::Vector2f(0, 0);
	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
	mShape.setTexture(mCurrentTexture);
	mPlayerAnimation = new Animation(PLAYER_PATH, sf::IntRect(0,0,40,120), 4, false);
	mPlayerAnimation->SetStartSize(0, 0, 40, 120);

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

void Player::OnUpdate()
{
	mShape.move(mDepl);

	immuneProgress += GetDeltaTime();

	mPlayerAnimation->Update(GetDeltaTime());
	mShape.setTextureRect(*mPlayerAnimation->GetTextureRect());

	if (!reverse && mDepl.x < 0)
	{
		reverse = true;
		mPlayerAnimation->SetReverseSprite(true);
	}
	else if (reverse && mDepl.x > 0)
	{
		reverse = false;
		mPlayerAnimation->SetReverseSprite(false);
	}

	mStateMachine.Update();
}

void Player::OnCollision(Entity* pCollideWith)
{
	AABBCollider c1 = GetAABBCollider();

	AABBCollider c2 = pCollideWith->GetAABBCollider();

	int face = Utils::GetFace(c1, c2);

	if (pCollideWith->IsTag(PlatFormerScene::Tag::GROUND) || pCollideWith->IsTag(PlatFormerScene::Tag::Amovible))
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

	if (immuneProgress < immuneTime)
	{
		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Damagezone))
	{
		TakeDamage(1);
		immuneProgress = 0;

		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::ENEMY) || pCollideWith->IsTag(PlatFormerScene::Tag::ENEMY_BULLET))
	{
		TakeDamage(1.f);
		std::cout << "HP : " << GetHP() << std::endl;
		immuneProgress = 0;

		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::BOSS) || pCollideWith->IsTag(PlatFormerScene::Tag::BOSS_BULLET))
	{
		TakeDamage(3.f);
		immuneProgress = 0;

		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::KEY))
	{
		haseKey = true;
	}
}

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
	mDepl = sf::Vector2f(mPlayerParameters.mPlayerSpeed * deltaTime, 0);
}

void Player::MoveLeft(float deltaTime)
{
	mDepl = sf::Vector2f(-mPlayerParameters.mPlayerSpeed * deltaTime, 0);
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

	mDepl = sf::Vector2f(10 * stickX / 100, 0);

	if (mDepl.x != 0.f)
		mIsMoving = true;
	else
		mIsMoving = false;
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
	mIsMoving = false;
}

void Player::ChangeStatic(bool stat)
{
	SetStatic(stat);
}

bool Player::HaseKey()
{
	return haseKey;
}