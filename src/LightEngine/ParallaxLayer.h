#pragma once
#include <SFML/Graphics.hpp>

class Player;

class ParallaxLayer
{
	sf::Sprite mSprite1;
	sf::Sprite mSprite2;

	sf::Image mImage;

	float mSpeed;

public:
	ParallaxLayer(sf::Texture* texture, float speed);

	void Update(Player* player, sf::Vector2f oldPos);
	void SetPosition(sf::Vector2f posPlayer);
	void SetPositionY(float posY);

	void Draw(sf::RenderWindow& window);
};