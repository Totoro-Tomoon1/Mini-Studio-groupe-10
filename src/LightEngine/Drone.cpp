#include "Drone.h"
#include "PlatFormerScene.h"
#include "AssetManager.h"
#include "DroneAction.h"
#include "DroneCondition.h"
#include "Debug.h"
#include "Chest.h"
#include "Utils.h"
#include "Bullet.h"
#include "PlatformAmovible.h"

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

	mStateMachine.SetState(State::Idle);
}

void Drone::OnUpdate()
{
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
		mDroneAnimation->SetReverseSprite(true);
	}
	else if (reverse && mDepl.x > 0)
	{
		reverse = false;
		mDroneAnimation->SetReverseSprite(false);
	}

	mStateMachine.Update();
}

void Drone::OnCollision(Entity* pCollideWith)
{
	AABBCollider c1 = GetAABBCollider();

	AABBCollider c2 = pCollideWith->GetAABBCollider();

	int face = Utils::GetFace(c1, c2);

	if (pCollideWith->IsTag(PlatFormerScene::Tag::CHEST))
	{
		mCanHack = true;
		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::Key))
	{
		hasKey = true;
		pCollideWith->Destroy();
		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::PLAYER) && !isUnlocked)
	{
		isUnlocked = true;
		Undisplay();
		return;
	}

	if (pCollideWith->IsTag(PlatFormerScene::Tag::HACKING_ZONE) && mCanHack)
	{
		PlatformAmovible* pPlatform = dynamic_cast<PlatformAmovible*>(pCollideWith);
		pPlatform->IsGettingHacked();
		return;
	}

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

void Drone::OnFixedUpdate(float deltaTime)
{
	mShape.move(mDepl);
	sf::Vector2f camCenter = GetScene<PlatFormerScene>()->GetCamera().GetView().getCenter();
	sf::Vector2f myPosition = mShape.getPosition();

	if (myPosition.x > camCenter.x + 640.f)
		mShape.setPosition(camCenter.x + 640.f, myPosition.y);
	if (myPosition.x < camCenter.x - 640.f)
		mShape.setPosition(camCenter.x - 640.f, myPosition.y);
	if (myPosition.y > camCenter.y + 360.f)
		mShape.setPosition(myPosition.x, camCenter.y + 360.f);
	if (myPosition.x > camCenter.y + 360.f)
		mShape.setPosition(myPosition.x, camCenter.y + 360.f);

	mIsMoving = false;
	mIsShooting = false;
}

//Pour l'affichage debug
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

void Drone::MoveRight(float deltaTime)
{
	mDepl.x += mDroneParameters.mSpeed * deltaTime;
}

void Drone::MoveLeft(float deltaTime)
{
	mDepl.x -= mDroneParameters.mSpeed * deltaTime;
}

void Drone::MoveUp(float deltaTime)
{
	mDepl.y -= mDroneParameters.mSpeed * deltaTime;
}

void Drone::MoveDown(float deltaTime)
{
	mDepl.y += mDroneParameters.mSpeed * deltaTime;
}

bool Drone::IsMoving()
{
	return mIsMoving;
}

bool Drone::CanHack()
{
	return mCanHack;
}

void Drone::Input()
{
	float deltaTime = GetDeltaTime();

	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	if (std::abs(stickX) < 10)
		stickX = 0;

	if (std::abs(stickY) < 10)
		stickY = 0;

	mDepl = sf::Vector2f(10 * stickX / 100, 10 * stickY / 100);
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