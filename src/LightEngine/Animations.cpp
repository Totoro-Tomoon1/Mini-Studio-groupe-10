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
			std::cout << mCurrentIndex << std::endl;
			mCurrentIndex = (mCurrentIndex + 1) % mNumberFrames;
		}

		else if (!mReverse)
		{
			std::cout << mCurrentIndex << std::endl;
			mCurrentIndex = mCurrentIndex + 1;
			if (mCurrentIndex + 1 == mNumberFrames)
				mReverse = true;
		}
		else
		{
			std::cout << mCurrentIndex << std::endl;
			mCurrentIndex -= 1;
			if (mCurrentIndex == 0)
				mReverse = false;
		}
		
		mTextureRect = sf::IntRect(mXSize * mCurrentIndex + mXStart,mYStart,mXSize,mYSize);
	}
}

sf::IntRect* Animation::GetTextureRect()
{
	return &mTextureRect;
}
