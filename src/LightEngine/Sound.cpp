#include "Sound.h"
#include <iostream>

void Sound::Load(const char* path)
{
	if (!mBuffer.loadFromFile(path))
	{
		std::cout << "Erreur de chargement du son !!!!" << std::endl;
	}
	mSound.setBuffer(mBuffer);
}

void Sound::Play()
{
	mSound.play();
}

sf::Sound* Sound::GetSound()
{
	return &mSound;
}