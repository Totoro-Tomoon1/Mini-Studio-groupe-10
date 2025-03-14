#pragma once

#include "GameManager.h"

#include <list>
#include "Camera.h"

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

	Camera mCamera;

public:

	enum Tag
	{
		PLAYER,
		GROUND,
		DRONE,
		PROJECTILE
	};

	/*int mLaneLevel[1] = { 0 };
	AABB mAreas[1];*/
		
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override {};
	void OnLateUpdate() override;


};

