#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#define FIXED_DT 0.01667f
#define GRAVITY_ACCELERATION 9.81f
#define PLAYER_PATH "../../../res/MODELSHEET_ANIM_MIRA.png"
#define CHEST_PATH "../../../res/MODELSHEET_OUVERTURE_COFFRE.png"

class Entity;
class Scene;
class Debug;
class Camera;
class AssetManager;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	Scene* mpScene;

	float mDeltaTime;
	float mAccumulatedDt = 0.f;

	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

	AssetManager* mAssetManager;

	Camera* cam;

private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void FixedUpdate();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	sf::RenderWindow* GetWindow() const { return mpWindow; }

public:
	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };
	AssetManager* GetAssetManager() { return mAssetManager; };

	void SetCamera(Camera& camera);
	void DestroyAllEntities();

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"