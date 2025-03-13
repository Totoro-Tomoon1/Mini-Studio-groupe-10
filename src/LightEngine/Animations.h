#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"

class Animation
{
	//sf::Texture* mSpriteSheet;
	int mNumberFrames;
	int mCurrentIndex = 0;
	float mDuration = 0.1f;
	sf::IntRect mTextureRect;
	int mXStart;
	int mYStart;
	int mXSize;
	int mYSize;

public:
	Animation(const char* path, sf::IntRect rect, int nbFrame);

	void SetStartSize(int xStart, int yStart, int xSize, int ySize);

	void Update(float deltaTime);

	sf::IntRect* GetTextureRect();
};

