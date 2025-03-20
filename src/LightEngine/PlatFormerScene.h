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
class Burrefly;

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

	bool playerSelected = true;

	ParallaxManager* mParallaxManager;

	bool UpPressed = false;

	//pour background
	sf::Texture* backgroundTexture1 = new sf::Texture;
	sf::Texture* backgroundTexture2 = new sf::Texture;
	sf::Texture* backgroundTexture3 = new sf::Texture;
	sf::Texture* backgroundTexture4 = new sf::Texture;
	sf::Texture* backgroundTexture5 = new sf::Texture;

	Burrefly* mButterfly;

	bool hasKey = false;

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
		BOSS_BULLET,
		Key,
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

	void GenerateMap();
};