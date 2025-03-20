#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"

class Animation
{
	int mNumberFrames;
	int mCurrentIndex = 0;
	float mDuration = 0.1f;
	sf::IntRect mTextureRect;
	int mXStart;
	int mYStart;
	int mXSize;
	int mYSize;
	int spaceX = 0;

	bool mIsReapated = false;
	bool mReverse = false;
	bool reverseSprite = false;

public:
	Animation(const char* path, sf::IntRect rect, int nbFrame, bool isReapated);

	void SetStartSize(int xStart, int yStart, int xSize, int ySize);

	void Update(float deltaTime);

	sf::IntRect* GetTextureRect();

	void SetNewY(int y) { mYStart = y; };
	void SetNewXsize(int x) { mXSize = x; }
	void SetReverseSprite(bool reverse) { reverseSprite = reverse; }
	void SetNBFrame(int frame) { mNumberFrames = frame; }
	void SetSpaceX(int space) { spaceX = space; }
};