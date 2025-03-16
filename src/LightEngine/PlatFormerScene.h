#pragma once

#include "GameManager.h"

#include <list>
#include "Camera.h"

class Player;
class Music;
class Sound;

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

	Music* mMusic;
	Sound* mSound;

public:

	enum Tag
	{
		PLAYER,
		GROUND,
		DRONE,
		HACKING_ZONE,
	};

	/*int mLaneLevel[1] = { 0 };
	AABB mAreas[1];*/
		
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override {};
	void OnLateUpdate() override;


};

