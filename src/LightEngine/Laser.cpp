#include "Laser.h"
#include "AssetManager.h"

#define Lazer_Path "../../../res/MODELSHEET_FX_BOSSE.png"

void Laser::OnInitialize()
{
	mDirection = { 0.f, 0.f };

	mTexture = GameManager::Get()->GetAssetManager()->GetTexture(Lazer_Path);
	mShape.setTexture(mTexture);
	mShape.setTextureRect(sf::IntRect(1743, 27, 283, 238));
}

void Laser::OnCollision(Entity* other)
{
}

void Laser::OnUpdate()
{
	mProcess += GameManager::Get()->GetDeltaTime();

	if (mProcess > mLifeTime)
		Destroy();
}