#include "Platform.h"
#include "AssetManager.h"
#include "Animations.h"

#define Platform_Path "../../../res/Plate-forme.png"

void Platform::OnInitialize()
{
	
	
}

void Platform::SetTexture(int type)
{
	mTexture = GameManager::Get()->GetAssetManager()->GetTexture(Platform_Path);
	mShape.setTexture(mTexture);
	switch (type)
	{
	case 3:
	{
		mShape.setTextureRect(sf::IntRect(824, 768, 275, 333));
	}
	break;
	}
}

void Platform::OnUpdate()
{
}

void Platform::OnCollision(Entity* other)
{
}