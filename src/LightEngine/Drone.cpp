#include "Drone.h"
#include "PlatFormerScene.h"
#include "AssetManager.h"
#include "DroneAction.h"
#include "DroneCondition.h"
#include "Debug.h"
#include "Utils.h"
#include "Bullet.h"

#define Drone_Path "../../../res/MODELSHEET_FRED_BULLE.png"

Drone::Drone() : mStateMachine(this, (int)State::Count)
{
}

void Drone::OnInitialize()
{
	SetTag(PlatFormerScene::Tag::DRONE);
	SetRigidBody(true);
	SetLife(20.f);

	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(Drone_Path);
	mShape.setTexture(mCurrentTexture);
	mDroneAnimation = new Animation(Drone_Path, sf::IntRect(50, 0, 50, 60), 10, true);
	mDroneAnimation->SetStartSize(20, 0, 50, 60);

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
	mShape.move(mDepl);
	mShape.setTextureRect(*mDroneAnimation->GetTextureRect());

	if (GetHP() <= 0)
	{
		Destroy();
		std::cout << "You're dead" << std::endl;
	}

	imuuneProgresse += GetDeltaTime();

	if (!reverse && mDepl.x < 0)
	{
		reverse = true;
		//mPlayerAnimation->SetNewY(135);
		mDroneAnimation->SetReverseSprite(true);
	}
	else if (reverse && mDepl.x > 0)
	{
		reverse = false;
		//mPlayerAnimation->SetNewY(0);
		mDroneAnimation->SetReverseSprite(false);
	}

	mStateMachine.Update();
	Debug::DrawText(0, 0, std::to_string(mDroneParameters.mMinSpeed), sf::Color::White);
	Debug::DrawText(GetPosition().x + 50.f, GetPosition().y + 50.f, GetStateName((Drone::State)mStateMachine.GetCurrentState()), sf::Color::Red);
}

void Drone::OnCollision(Entity* pCollideWith)
{
	AABBCollider c1 = GetAABBCollider();

	AABBCollider c2 = pCollideWith->GetAABBCollider();

	int face = Utils::GetFace(c1, c2);


	if (pCollideWith->IsTag(PlatFormerScene::Tag::HACKING_ZONE))
	{
		mCanHack = true;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Key))
	{
		hasKey = true;
		pCollideWith->Destroy();
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::PLAYER) && !isUnlocked)
	{
		isUnlocked = true;
		Undisplay();
		if (imuuneProgresse < immuneTime)
		{
			return;
		}

		if (pCollideWith->IsTag(PlatFormerScene::Tag::ENEMY_BULLET) || pCollideWith->IsTag(PlatFormerScene::Tag::ENEMY))
		{
			TakeDamage(1.f);
			imuuneProgresse = 0.f;

			return;
		}

		if (pCollideWith->IsTag(PlatFormerScene::Tag::BOSS) || pCollideWith->IsTag(PlatFormerScene::Tag::BOSS_BULLET))
		{
			TakeDamage(3.f);
			imuuneProgresse = 0.f;

			return;
		}
	}
}

void Drone::OnFixedUpdate(float deltaTime) //Update physique
{
	mIsMoving = false;
	mIsShooting = false;
	mCanHack = false;
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
	mDepl.x += mDroneParameters.mMinSpeed * deltaTime;
}

void Drone::MoveLeft(float deltaTime)
{
	mDepl.x -= mDroneParameters.mMinSpeed * deltaTime;
}

void Drone::MoveUp(float deltaTime)
{
	mDepl.y -= mDroneParameters.mMinSpeed * deltaTime;
}

void Drone::MoveDown(float deltaTime)
{
	mDepl.y += mDroneParameters.mMinSpeed * deltaTime;
}

bool Drone::IsMoving()
{
	return mIsMoving;
}

bool Drone::CanHack()
{
	return mCanHack;
}

//void Drone::Shoot(float deltaTime)
//{		
//	Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
//	b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
//}

void Drone::Input()
{
	float deltaTime = GetDeltaTime();

	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	if (std::abs(stickX) < 10)
		stickX = 0;

	if (std::abs(stickY) < 10)
		stickY = 0;

	//std::cout << 10 * stickX / 100 << std::endl;

	mDepl = sf::Vector2f(10 * stickX / 100, 10 * stickY / 100);

	/*mDepl = sf::Vector2f(0, 0);

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
	}*/
	

	//mShape.move(mDepl);
}

void Drone::Undisplay()
{
	SetToDraw(false);
	SetRigidBody(false);
}

void Drone::Display(sf::Vector2f posPlayer)
{
	SetToDraw(true);
	SetRigidBody(true);
	SetPosition(posPlayer.x - 50, posPlayer.y - 50);
}

void Drone::ActivateInput()
{
	isInputActive = true;
}

void Drone::DesactivateInput()
{
	isInputActive = false;
}

bool Drone::GetIsInputActivate()
{
	return isInputActive;
}

void Drone::ResetmDepl()
{
	mDepl = sf::Vector2f(0, 0);
}

bool Drone::GetIsUnlocked()
{
	return isUnlocked;
}

void Drone::ChangeIsUnlocked()
{
	isUnlocked = !isUnlocked;
}

void Drone::Shoot(float deltaTime)
{		
	Bullet* b = CreateEntity<Bullet>(sf::Vector2f(10.f, 10.f), sf::Color::Yellow);
	b->SetPosition(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y / 2);
	b->SetDirection(7,0);
	b->SetTag(PlatFormerScene::Tag::PLAYER_BULLET);
}