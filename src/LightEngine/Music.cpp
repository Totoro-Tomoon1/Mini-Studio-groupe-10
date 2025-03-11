#include "Music.h"

void Music::Load(const char* path)
{
	if (!mMusic.openFromFile(path))
		return;
}

void Music::Play()
{
	mMusic.play();
}

void Music::Stop()
{
	mMusic.stop();
}
