#pragma once

#include "GameManager.h"

#include <list>
#include "Camera.h"

class Player;
class Music;
class Sound;
class ParallaxManager;
class Drone;

namespace sf
{
	class Event;
}

class PlatFormerScene : public Scene
{
private:
	Entity* pPlayer;
	Entity* pGround;

	Camera mCamera;

	Music* mMusic;
	Sound* mSound;

	Player* mPlayer;
	Drone* mDrone;

	bool playerSelected = true;

	ParallaxManager* mParallaxManager;

	bool UpPressed = false;

public:

	enum Tag
	{
		PLAYER,
		GROUND,
		DRONE,
		HACKING_ZONE,
		Damagezone,
		Fallzone
	};
		
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void OnLateUpdate() override;
	void Draw(sf::RenderWindow& pRenderWindow) override;

	void CreateBackGround();

	void GenerateMap();
};

