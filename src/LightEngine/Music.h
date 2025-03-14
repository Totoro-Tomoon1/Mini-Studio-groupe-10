#pragma once
#include <SFML/Audio.hpp>

class Music
{
	sf::Music mMusic;

public:
	void Load(const char* path);
	void Play();
};

