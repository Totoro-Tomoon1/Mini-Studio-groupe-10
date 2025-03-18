#include "PlatformAmovible.h"
#include "PlatFormerScene.h"
#include "Debug.h"
#include <iostream>
#include "Utils.h"

void PlatformAmovible::OnUpdate()
{
	//std::cout << GetPosition().x << " / " << GetPosition().y << std::endl;
	Move(GetPosition().x, GetPosition().y +200 , 50);
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
	if (mActive == true && IsTag(PlatFormerScene::Tag::ACTIVATE_ZONE))
	{
	     mIsStatic = false;
		
		
	}

	if (mActive == true && IsTag(PlatFormerScene::Tag::HACKING_ZONE))
	{
		GoToPosition(x, y, 50);
		mIsMoving = true;
		
	}
	
	mActive = false;
}

