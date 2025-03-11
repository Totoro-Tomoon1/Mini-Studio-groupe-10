#include "PlatFormerScene.h"

#include "Player.h"
#include "DummyEntity.h"
#include "Debug.h"

#include <iostream>


void PlatFormerScene::OnInitialize()
{

	pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(640, 200), sf::Color::Red);
	pGround->SetPosition(0, 600);
	pGround->SetRigidBody(true);

	pPlayer = CreateRectangleEntity<Player>(sf::Vector2f(100,200), sf::Color::Red);
	pPlayer->SetPosition(100, 400);
	pPlayer->SetRigidBody(true);
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::JoystickButtonPressed)
		return;

	std::cout << "Mannette connecte" << std::endl;


}

void PlatFormerScene::OnUpdate()
{
	

}
