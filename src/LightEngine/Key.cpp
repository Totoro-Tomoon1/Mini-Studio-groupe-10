#include "Key.h"
#include "AssetManager.h"

#define Key_Path "../../../res/MODEL_SHEET_CLE.png"

void Key::OnInitialize()
{
	mTexture = GameManager::Get()->GetAssetManager()->GetTexture(Key_Path);
	mShape.setTexture(mTexture);
	mShape.setTextureRect(sf::IntRect(22, 60, 31, 79));
}
