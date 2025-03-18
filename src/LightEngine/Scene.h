#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnLateUpdate() = 0;
	virtual void Draw(sf::RenderWindow& pRenderWindow) {};

public:

	template<typename T>
	T* CreateRectangleEntity(sf::Vector2f size, const sf::Color& color);

	float GetDeltaTime() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	sf::View GetView();

	friend GameManager;
};

#include "Scene.inl"