#include "Chest.h"
#include "PlatFormerScene.h"
#include "Drone.h"

void Chest::OnOpen()
{
	Destroy();
}

void Chest::OnCollision(Entity* pCollideWith)
{
	if (pCollideWith->IsTag(PlatFormerScene::Tag::DRONE))
	{
		Drone* pDrone = dynamic_cast<Drone*>(pCollideWith);

		if(pDrone->HaseKey())
			OnOpen();
	}
}
