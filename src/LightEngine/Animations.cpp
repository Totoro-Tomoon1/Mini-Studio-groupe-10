#include "Animations.h"
#include "AssetManager.h"

Animation::Animation(const char* path, sf::IntRect rect, int nbFrame)
{
	mTextureRect = rect;
	mNumberFrames = nbFrame;
}

void Animation::SetStartSize(int xStart, int yStart, int xSize, int ySize)
{
	mXStart = xStart;
	mYStart = yStart;
	mXSize = xSize;
	mYSize = ySize;
}

void Animation::Update(float deltaTime)
{
	mDuration -= deltaTime;

	if (mDuration <= 0)
	{
		mDuration += 0.1f;
		mCurrentIndex = (mCurrentIndex + 1) % mNumberFrames;
		mTextureRect = sf::IntRect(mXSize * mCurrentIndex + mXStart,mYStart,mXSize,mYSize);
	}
}

sf::IntRect* Animation::GetTextureRect()
{
	return &mTextureRect;
}
