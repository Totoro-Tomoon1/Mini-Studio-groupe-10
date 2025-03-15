#include "ParallaxManager.h"
#include "ParallaxLayer.h"
#include "GameManager.h"
#include "Player.h"

void ParallaxManager::AddLayers(ParallaxLayer newLayer)
{
	newLayer.SetPosition(mPlayer->GetPosition(0.5f, 0.5f));
	mLayer.push_back(newLayer);
}

void ParallaxManager::SetPlayer(Player* player)
{
	mPlayer = player;
}

void ParallaxManager::Update(float dt)
{
	std::cout << mPlayer->GetPosition().x << "\t" << mPlayer->GetPosition().y << std::endl;

	for (auto& layer : mLayer)
	{
		layer.Update(mPlayer);
		layer.SetPositionY(mPlayer->GetPosition(0.5f, 0.5f).y - mPlayer->GetScene()->GetWindowHeight() / 2);
	}
}

void ParallaxManager::Draw(sf::RenderWindow& pRenderWindow)
{
	for (auto& layer : mLayer)
	{
		layer.Draw(pRenderWindow);
	}
}
