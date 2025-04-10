#include "Animations.h"
#include "AssetManager.h"

Animation::Animation(const char* path, sf::IntRect rect, int nbFrame, bool isReapeted)
{
	mTextureRect = rect;
	mNumberFrames = nbFrame;
	mIsReapated = isReapeted;
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

		if (!mIsReapated)
		{
			mCurrentIndex = (mCurrentIndex + 1) % mNumberFrames;
		}

		else if (!mReverse)
		{
			mCurrentIndex = mCurrentIndex + 1;
			if (mCurrentIndex + 1 == mNumberFrames)
				mReverse = true;
		}
		else
		{
			mCurrentIndex -= 1;
			if (mCurrentIndex == 0)
				mReverse = false;
		}

		if (reverseSprite)
		{
			mTextureRect = sf::IntRect(mXSize * mCurrentIndex + mXStart + mXSize + spaceX * mCurrentIndex, mYStart, -mXSize , mYSize);
		}
		else if (!reverseSprite)
		{
			mTextureRect = sf::IntRect(mXSize * mCurrentIndex + mXStart + spaceX * mCurrentIndex, mYStart, mXSize, mYSize);
		}
		
		
	}

	
}

sf::IntRect* Animation::GetTextureRect()
{
	return &mTextureRect;
}