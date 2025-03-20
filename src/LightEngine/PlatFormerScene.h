#pragma once

#include "GameManager.h"
#include "FPSCounter.h"
#include <list>
#include "Camera.h"

class Player;
class Drone;
class Music;
class Sound;
class ParallaxManager;
class Drone;
class Burrefly;
class Chest;

namespace sf
{
	class Event;
}

class PlatFormerScene : public Scene
{
private:
	Camera mCamera;

	Music* mMusic;
	Sound* mSound;

	Player* mPlayer;
	Drone* mDrone;
	FPSCounter fpsCounter;
	Chest* mChest;

	bool playerSelected = true;

	ParallaxManager* mParallaxManager;

	bool UpPressed = false;

	sf::Texture* backgroundTexture1 = new sf::Texture;
	sf::Texture* backgroundTexture2 = new sf::Texture;
	sf::Texture* backgroundTexture3 = new sf::Texture;
	sf::Texture* backgroundTexture4 = new sf::Texture;
	sf::Texture* backgroundTexture5 = new sf::Texture;

	Burrefly* mButterfly;

public:

	enum Tag
	{
		PLAYER,
		GROUND,
		DRONE,
		ENEMY,
		BOSS,
		CHEST,
		HACKING_ZONE,
		Damagezone,
		Fallzone,
		PLAYER_BULLET,
		ENEMY_BULLET,
		ACTIVATE_ZONE,
		BOSS_BULLET,
		KEY,
		Amovible

	};
		
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void OnLateUpdate() override;
	void Draw(sf::RenderWindow& pRenderWindow) override;
	Player* GetPlayer();
	Drone* GetDrone();
	void CreateBackGround();
	void Reset();
	Camera GetCamera() { return mCamera; }
	void GenerateMap();
};