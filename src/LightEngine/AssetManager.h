#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class AssetManager
{
	std::map<const char*, sf::Texture*> mTextures;

private:
	sf::Texture* LoadTexture(const char* path);

public:
	AssetManager();

	sf::Texture* GetTexture(const char* path);

};

