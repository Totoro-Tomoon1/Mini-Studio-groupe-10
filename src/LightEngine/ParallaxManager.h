#pragma once

class ParallaxLayer;
class Player;
#include <SFML/Graphics.hpp>
#include <iostream>

class ParallaxManager
{
	std::vector<ParallaxLayer> mLayer;

	Player* mPlayer;

public:
	void AddLayers(ParallaxLayer newLayer);
	void SetPlayer(Player* player);

	void Update(float dt);
	void Draw(sf::RenderWindow& pRenderWindow);
};

