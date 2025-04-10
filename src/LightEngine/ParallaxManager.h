#pragma once

class ParallaxLayer;
class Player;
class Burrerfly;
#include <SFML/Graphics.hpp>
#include <iostream>

class ParallaxManager
{
	std::vector<ParallaxLayer> mLayer;

	Player* mPlayer;
	sf::Vector2f oldPos;

public:
	void AddLayers(ParallaxLayer newLayer);
	void SetPlayer(Player* player);

	void Update(float dt);
	void Draw(sf::RenderWindow& pRenderWindow);
};