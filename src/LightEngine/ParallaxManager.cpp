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
	oldPos = player->GetPosition();
}

void ParallaxManager::Update(float dt)
{
	for (auto& layer : mLayer)
	{
		layer.Update(mPlayer, oldPos);
		layer.SetPositionY(mPlayer->GetPosition(0.5f, 0.5f).y - mPlayer->GetScene()->GetWindowHeight() / 2);
	}

	oldPos = mPlayer->GetPosition();
}

void ParallaxManager::Draw(sf::RenderWindow& pRenderWindow)
{
	for (auto& layer : mLayer)
	{
		layer.Draw(pRenderWindow);
	}
}
