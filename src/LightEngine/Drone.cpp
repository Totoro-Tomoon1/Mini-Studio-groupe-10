#include "Drone.h"
#include "PlatFormerScene.h"
#include "AssetManager.h"
#include "DroneAction.h"
#include "DroneCondition.h"
#include "Debug.h"
#include "Utils.h"
#include "Bullet.h"

Drone::Drone() : mStateMachine(this, (int)State::Count)
{
}

void Drone::OnInitialize()
{
	SetTag(PlatFormerScene::Tag::DRONE);
	SetRigidBody(true);

	//Idle
	{
		DroneAction_Idle* pIdle = mStateMachine.CreateAction<DroneAction_Idle>(State::Idle);

		//-> Moving
		{
			auto transition = pIdle->CreateTransition(State::Moving);

			transition->AddCondition<DroneCondition_IsMoving>();
		}

		//-> Shooting
		{
			auto transition = pIdle->CreateTransition(State::Shooting);

			transition->AddCondition<DroneCondition_IsShooting>();
		}

		//-> Hacking
		{
			auto transition = pIdle->CreateTransition(State::Hacking);

			transition->AddCondition<DroneCondition_TryHacking>();
			transition->AddCondition<DroneCondition_CanHack>();
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

		//-> Shooting
		{
			auto transition = pMoving->CreateTransition(State::Shooting);

			transition->AddCondition<DroneCondition_IsShooting>();
		}
	}

	//Shooting	
	{
		DroneAction_Shoot* pJumping = mStateMachine.CreateAction<DroneAction_Shoot>(State::Shooting);

		//-> Idle
		{
			auto transition = pJumping->CreateTransition(State::Idle);

			transition->AddCondition<DroneCondition_IsShooting>(false);
		}

		//-> Moving
		{
			auto transition = pJumping->CreateTransition(State::Moving);

			transition->AddCondition<DroneCondition_IsShooting>(false);
			transition->AddCondition<DroneCondition_IsMoving>();
		}
	}

	//Hacking
	{
		DroneAction_Hacking* pFalling = mStateMachine.CreateAction<DroneAction_Hacking>(State::Hacking);

		//-> Idle
		{
			auto transition = pFalling->CreateTransition(State::Idle);

			transition->AddCondition<DroneCondition_TryHacking>(false);
		}

		//-> Moving
		{
			auto transition = pFalling->CreateTransition(State::Moving);

			transition->AddCondition<DroneCondition_IsMoving>();
		}
	}

	mStateMachine.SetState(State::Idle);
}

void Drone::OnUpdate() //Update non physique (pour les timers etc...)
{
	mStateMachine.Update();
	Debug::DrawText(0, 0, std::to_string(mDroneParameters.mMinSpeed), sf::Color::White);
	Debug::DrawText(GetPosition().x + 50.f, GetPosition().y + 50.f, GetStateName((Drone::State)mStateMachine.GetCurrentState()), sf::Color::Red);
}

void Drone::OnCollision(Entity* pCollideWith)
{
	AABBCollider c1 = GetAABBCollider();

	AABBCollider c2 = pCollideWith->GetAABBCollider();

	int face = Utils::GetFace(c1, c2);

	//std::cout << "Collide with face : " << face << std::endl;

	if (pCollideWith->IsTag(PlatFormerScene::Tag::HACKING_ZONE))
	{
		mCanHack = true;
	}
}

void Drone::OnFixedUpdate(float deltaTime) //Update physique
{
	mIsMoving = false;
	mIsShooting = false;
	mCanHack = false;

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
}

//Pour l'affichage debug
const char* Drone::GetStateName(State state) const
{
	switch (state)
	{
	case Idle: return "Idle";
	case Moving: return "Moving";
	case Shooting: return "Shooting";
	case Hacking: return "Hacking";
	default: return "Unknown";
	}
}

void Drone::MoveRight(float deltaTime)
{
	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

		//mPlayerPosition.x += mPlayerParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x + mDroneParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}

void Drone::MoveLeft(float deltaTime)
{

	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

		//mPlayerPosition.x -= mPlayerParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x - mDroneParameters.mMinSpeed * deltaTime, mShape.getPosition().y));
}

void Drone::MoveUp(float deltaTime)
{

	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

		//mPlayerPosition.x -= mPlayerParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x, mShape.getPosition().y - mDroneParameters.mMinSpeed * deltaTime));
}

void Drone::MoveDown(float deltaTime)
{

	/*mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;*/

		//mPlayerPosition.x -= mPlayerParameters.mMinSpeed * deltaTime;
	mShape.setPosition(sf::Vector2f(mShape.getPosition().x, mShape.getPosition().y + mDroneParameters.mMinSpeed * deltaTime));
}

bool Drone::IsMoving()
{
	return mIsMoving;
}

bool Drone::CanHack()
{
	return mCanHack;
}

void Drone::Shoot(float deltaTime)
{		
	Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
	b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
}
