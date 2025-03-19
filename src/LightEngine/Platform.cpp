#include "Platform.h"
#include "AssetManager.h"
#include "Animations.h"
#include "Player.h"

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
	float dist = sqrt((GetPosition().x - GetScene()->GetView().getCenter().x) * (GetPosition().x - GetScene()->GetView().getCenter().x) + (GetPosition().y - GetScene()->GetView().getCenter().y) * (GetPosition().y - GetScene()->GetView().getCenter().y));

	if (dist > 660)
	{
		//SetToDraw(false);
		mShape.setTexture(nullptr);
	}
	else
	{
		//SetToDraw(true);
		mShape.setTexture(mTexture);
	}
}

void Platform::OnCollision(Entity* other)
{
}