#include "Music.h"
#include <iostream>

void Music::Load(const char* path)
{
	if (!mMusic.openFromFile(path))
	{
		std::cout << "Erreur de chargement de la music !!!!" << std::endl;
	}
}

void Music::Play()
{
	mMusic.play();
}

sf::Music* Music::GetMusic()
{
	return &mMusic;
}