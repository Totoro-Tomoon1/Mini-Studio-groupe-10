#include "AssetManager.h"
#include "GameManager.h"

sf::Texture* AssetManager::LoadTexture(const char* path)
{
    sf::Texture* pTexture = new sf::Texture();
    pTexture->loadFromFile(path);
    mTextures[path] = pTexture;

    return pTexture;
}

AssetManager::AssetManager()
{
    LoadTexture(PLAYER_PATH);
}

sf::Texture* AssetManager::GetTexture(const char* path)
{
    auto it = mTextures.find(path);

    if (it == mTextures.end())
        return LoadTexture(path);

    return it->second;
}
