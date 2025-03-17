#pragma once
#include <SFML/Graphics.hpp>

class Player;

class ParallaxLayer
{
	sf::Sprite mSprite1;
	sf::Sprite mSprite2;
	//sf::Sprite mSprite3;
	//sf::Sprite mSprite4;
	sf::Image mImage;
	/*sf::Image mGrayscaleImage;
	sf::Sprite mGrayscaleSprite;*/
	//sf::Image mGrayscaleImage;
	float mSpeed;

	//sf::Texture mGrayscaleTexture;

	//Player* mPlayer;

public:
	ParallaxLayer(sf::Texture* texture, float speed);

	void Update(Player* player);
	void SetPosition(sf::Vector2f posPlayer);
	void SetPositionY(float posY);
	//void ConvertToGrayscale();

	void Draw(sf::RenderWindow& window);
};

