#include "PlatFormerScene.h"
#include "DroneAction.h"
#include "DroneCondition.h"
#include "Drone.h"
#include "Projectile.h"
#include "Debug.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Drone::OnInitialize()
{
	SetTag(PlatFormerScene::Tag::DRONE);
	SetRigidBody(true);

	//SetPosition(600.f, 400.f);
	//mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
	//mShape.setTexture(mCurrentTexture);
	//mDroneAnimation = new Animation(PLAYER_PATH, sf::IntRect(0, 0, 1750, 2200), 9); //? modifier
	//mDroneAnimation->SetStartSize(0, 0, 1750, 2200);

	//Idle
	{
		DroneAction_Idle* pIdle = mStateMachine.CreateAction<DroneAction_Idle>(State::Idle);

		//-> Moving
		{
			auto transition = pIdle->CreateTransition(State::Moving);

			transition->AddCondition<DroneCondition_IsMoving>();
		}

		//-> Attack
		{
			auto transition = pIdle->CreateTransition(State::Shooting);

			transition->AddCondition<DroneCondition_IsShooting>();
		}

	}

	//Moving
	{
		DroneAction_Moving* pMoving = mStateMachine.CreateAction<DroneAction_Moving>(State::Moving);

		//-> Idle
		{
			auto transition = pMoving->CreateTransition(State::Idle);

			transition->AddCondition<DroneCondition_IsMoving>(false);
		}

		

	}

	//Shooting
	{
		DroneAction_Shooting* pShooting = mStateMachine.CreateAction<DroneAction_Shooting>(State::Shooting);

		//-> Idle
		{
			auto transition = pShooting->CreateTransition(State::Idle);

			transition->AddCondition<DroneCondition_IsShooting>(false);
		}
	}
}

void Drone::OnUpdate()
{

}

void Drone::OnCollision(Entity* pCollideWith)
{
	if (pCollideWith->IsTag(PlatFormerScene::Tag::GROUND))
	{
		SetGravity(false);
		mGravitySpeed = 0.f;
	}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		MoveUp(deltaTime);
		mIsMoving = true;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		MoveDown(deltaTime);
		mIsMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		Shoot(deltaTime);
		mIsShooting = true;
	}
}

const char* Drone::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Moving: return "Moving";
	case Shooting: return "Shooting";

	default: return "Unknown";
	}
}

void Drone::Shoot(float deltaTime)
{

	/*PlatFormerScene* pScene = ->GetScene<>();
	Projectile* pProjectile = ->CreateEntity<Projectile>(5.0f, sf::Color::Red);
	pProjectile->SetPosition(position.x, position.y);*/
}

void Drone::MoveRight(float deltaTime)
{
	mSpeed += mDroneParameters.mAcceleration * deltaTime;
	if (mSpeed > mDroneParameters.mMaxSpeed)
		mSpeed = mDroneParameters.mMaxSpeed;

	mDronePosition->x += mDroneParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x + mDroneParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}

void Drone::MoveLeft(float deltaTime)
{

	mSpeed += mDroneParameters.mAcceleration * deltaTime;
	if (mSpeed > mDroneParameters.mMaxSpeed)
		mSpeed = mDroneParameters.mMaxSpeed;

	mDronePosition->x -= mDroneParameters.mMinSpeed * deltaTime;
    mShape.setPosition(sf::Vector2f(mShape.getPosition().x - mDroneParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}

void Drone::MoveUp(float deltaTime)
{
	mSpeed += mDroneParameters.mAcceleration * deltaTime;
	if (mSpeed > mDroneParameters.mMaxSpeed)
		mSpeed = mDroneParameters.mMaxSpeed;

	mDronePosition->y += mDroneParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x - mDroneParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}

void Drone::MoveDown(float deltaTime)
{
	mSpeed += mDroneParameters.mAcceleration * deltaTime;
	if (mSpeed > mDroneParameters.mMaxSpeed)
		mSpeed = mDroneParameters.mMaxSpeed;

	mDronePosition->y -= mDroneParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x - mDroneParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}


bool Drone::IsMoving()
{
	return mIsMoving;
}

bool Drone::IsShooting()
{
	return mIsShooting;
}
