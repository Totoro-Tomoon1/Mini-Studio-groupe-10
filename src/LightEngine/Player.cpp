#include "Player.h"
#include "Scene.h"
#include "Debug.h"
#include "AssetManager.h"

Player::Player() : mStateMachine(this, State::Count)
{
}


//void Player::SetPosition(float x, float y, float ratioX, float ratioY)
//{
//	Entity::SetPosition(x, y, ratioX, ratioY);
//	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
//	mShape->setTexture(mCurrentTexture);
//}

void Player::OnInitialize()
{
	SetGravity(true);
	mShape = GetShape();
	mPlayerAnimation = new Animation(PLAYER_PATH, sf::IntRect(0, 32, 32, 32), 6); //� modifier
	mPlayerAnimation->SetStartSize(0, 32*7, 32, 32);
	//SetPosition(500.f, 500.f);
	mPlayerPosition = GetPosition();	
	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
	mShape->setTexture(mCurrentTexture);
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{
	mPlayerAnimation->Update(GetDeltaTime());
	mShape->setTextureRect(*mPlayerAnimation->GetTextureRect());
}

void Player::OnCollision(Entity* pCollideWith)
{
	
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
{
	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	bool A = sf::Joystick::isButtonPressed(0, 0);

	if (stickX < 0)
		MoveLeft(deltaTime);

	if (stickX > 0)
		MoveRight(deltaTime);

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

	mPlayerPosition.x += 100.f * deltaTime;
	mPlayerPosition.x += mSpeed * deltaTime;
}

void Player::MoveLeft(float deltaTime)
{
	
	mSpeed += mAcceleration * deltaTime;
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;

	mPlayerPosition.x -= 100.f * deltaTime;
	mPlayerPosition.x -= mSpeed * deltaTime;
}

void Player::OnFall(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime * 100.f;
}

void Player::OnJump(float deltaTime)
{
	mGravitySpeed -= 10.f;
}
