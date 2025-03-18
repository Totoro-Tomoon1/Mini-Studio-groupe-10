#pragma once

#include "GameManager.h"

#include <list>
#include "Camera.h"

class Player;
class Drone;
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
	
	Entity* pGround;
	Entity* pAmovible;
	Entity* pActivate;

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
		ENEMY,
		BOSS,
		HACKING_ZONE,
		Damagezone,
		Fallzone,
		PLAYER_BULLET,
		ENEMY_BULLET,
		ACTIVATE_ZONE,
		BOSS_BULLET

	};
		
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void OnLateUpdate() override;
	void Draw(sf::RenderWindow& pRenderWindow) override;
	Player* GetPlayer();
	Drone* GetDrone();
	void CreateBackGround();

	void GenerateMap();
};

