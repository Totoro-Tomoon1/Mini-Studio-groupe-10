#include "PlatFormerScene.h"

#include "Player.h"
#include "Debug.h"

#include <iostream>


void PlatFormerScene::OnInitialize()
{
	int width = GetWindowWidth();
	int height = GetWindowHeight();

	float playerRadius = height * 0.075f;

	Player* pPlayer;

	pPlayer = CreateEntity<Player>(playerRadius, sf::Color::Red);
	pPlayer->SetPosition(100, 100, 0.f, 0.5f);
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::JoystickButtonPressed)
		return;

	std::cout << "Mannette connecte" << std::endl;


}

void PlatFormerScene::OnUpdate()
{
	float stickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float stickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	bool A = sf::Joystick::isButtonPressed(0, 0);

	//if (stickX < 0)
	  //  pPlayer->GoToPosition(pPlayer->GetPosition().x - 5, pPlayer->GetPosition().y);

	//if (stickX > 0)
		//pPlayer->GoToPosition(pPlayer->GetPosition().x + 5, pPlayer->GetPosition().y);

}
