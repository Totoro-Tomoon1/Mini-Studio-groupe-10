#include "Chest.h"
#include "PlatFormerScene.h"

void Chest::OnOpen()
{
	
}

void Chest::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(PlatFormerScene::Tag::DRONE) && mHaveKey == true)
		OnOpen();
	
}
