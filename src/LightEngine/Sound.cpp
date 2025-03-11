#include "Sound.h"

void Sound::Load(const char* path)
{
	if (!mBuffer.loadFromFile(path))
		return;

	mSound.setBuffer(mBuffer);
}

void Sound::Play()
{
	
	mSound.play();
}
