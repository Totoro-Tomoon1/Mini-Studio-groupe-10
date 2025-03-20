#pragma once

#include "SFML/Graphics.hpp"

class Animation;

class Burrefly
{
	sf::View mView;

	sf::Texture* mTexture;
	sf::RectangleShape mShape;

	Animation* mButterflyAnimation;

	float spawnTimer = 3.f;
	float spawnProgress = 0.f;

public:
	void SetView(sf::View view) { mView = view; };
	void SetTexture();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& pWindow);
};