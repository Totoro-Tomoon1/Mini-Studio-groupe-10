
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SampleScene.h"
#include "PlatFormerScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main()
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "PlatFormerScene", 60, sf::Color::Cyan);
	
	pInstance->LaunchScene<PlatFormerScene>();

	return 0;
}