#include "PlatformAmovible.h"
#include "PlatFormerScene.h"
#include "Debug.h"
#include <iostream>
#include "Utils.h"

void PlatformAmovible::OnUpdate()
{
	std::cout << GetPosition().x << " / " << GetPosition().y << std::endl;
	Move(GetPosition().x, GetPosition().y -500 , 50);
}

void PlatformAmovible::OnCollision(Entity* other)
{
	if (other->IsTag(PlatFormerScene::Tag::PLAYER) && mIsMoving == false)
	{
		IsActive();
		
	}

}

bool PlatformAmovible::IsActive()
{
	mActive = true;
	return mActive;
}

void PlatformAmovible::Move(int x, int y, float speed)
{
	if (mActive == true)
	{
		GoToPosition(x, y, speed);
		mIsMoving = true;
	}
		
	
	mActive = false;
}

