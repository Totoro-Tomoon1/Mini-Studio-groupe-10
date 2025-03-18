#include "Burrefly.h"
#include <iostream>
#include "Animations.h"
#include "AssetManager.h"
#include <stdlib.h>

#define Butterfly_Path "../../../res/MODELSHEET_PAPILLON.png"

void Burrefly::SetTexture()
{
	mTexture = GameManager::Get()->GetAssetManager()->GetTexture(Butterfly_Path);
	mButterflyAnimation = new Animation(Butterfly_Path, sf::IntRect(0,6,50,44), 14, false);
	mButterflyAnimation->SetStartSize(0,6,50,44);
	mShape.setTexture(mTexture);
	mShape.setSize(sf::Vector2f(50 / 2, 44 / 2));
	srand(time(NULL)); //max only
}

void Burrefly::Update(float deltaTime)
{
	spawnProgress += deltaTime;

	if (spawnProgress >= spawnTimer)
	{
		spawnProgress = 0;
		float x = rand() % 1200 - 600;
		float y = rand() % 700 - 350;
		mShape.setPosition(sf::Vector2f(mView.getCenter().x + x , mView.getCenter().y + y));
	}

	mButterflyAnimation->Update(deltaTime);
	mShape.setTextureRect(*mButterflyAnimation->GetTextureRect());
}

void Burrefly::Draw(sf::RenderWindow& pWindow)
{
	pWindow.draw(mShape);
}
