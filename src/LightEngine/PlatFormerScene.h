#pragma once

#include "GameManager.h"

#include <list>

class Player;

namespace sf
{
	class Event;
}


//struct AABB
//{
//	int xMin;
//	int yMin;
//	int xMax;
//	int yMax;
//};

class PlatFormerScene : public Scene
{
private:
	Entity* pPlayer;
	Entity* pGround;

public:
	enum Tag
	{
		PLAYER,
		GROUND
	};

	/*int mLaneLevel[1] = { 0 };
	AABB mAreas[1];*/
		
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

