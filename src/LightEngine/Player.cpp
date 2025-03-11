#include "Player.h"
#include "AssetManager.h"

void Player::SetPosition(float x, float y, float ratioX, float ratioY)
{
	Entity::SetPosition(x, y, ratioX, ratioY);
	mCurrentTexture = GameManager::Get()->GetAssetManager()->GetTexture(PLAYER_PATH);
	mShape->setTexture(mCurrentTexture);
}

void Player::OnInitialize()
{
	mShape = GetShape();
	mPlayerAnimation = new Animation(PLAYER_PATH, sf::IntRect(0, 32, 32, 32), 6); //à modifier
	mPlayerAnimation->SetStartSize(0, 32*7, 32, 32);
	SetPosition(500.f, 500.f);
	mPlayerPosition = GetPosition();	
	
}

void Player::OnUpdate() //Update non physique (pour les timers etc...)
{
	mPlayerAnimation->Update(GetDeltaTime());
	mShape->setTextureRect(*mPlayerAnimation->GetTextureRect());
}

void Player::OnFixedUpdate(float deltaTime) //Update physique
{
	if (IsGravityOn()) //C'est un test du fall
	{
		Fall(deltaTime);
	}

	//Update de la position en fonction de si y'a eu Jump ou Fall
	mPlayerPosition.y += mGravitySpeed * deltaTime;

	SetPosition(mPlayerPosition.x, mPlayerPosition.y);
}

void Player::Fall(float deltaTime)
{
	mGravitySpeed += GRAVITY_ACCELERATION * deltaTime;	
}

void Player::Jump(float deltaTime)
{
	mGravitySpeed -= 10.f;
}
