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
	pGround->SetStatic(true);

	pPlayer = CreateRectangleEntity<Player>(sf::Vector2f(100,200), sf::Color::White);
	pPlayer->SetPosition(0, 0);
	pPlayer->SetRigidBody(true);

	mCamera.SetPosition(pPlayer->GetPosition());
	GameManager::Get()->SetCamera(mCamera);
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::JoystickButtonPressed)
		return;

	std::cout << "Mannette connecte" << std::endl;


}

void PlatFormerScene::OnLateUpdate()
{
	std::cout << pPlayer->GetPosition().y << "\t";
	mCamera.GetView().setCenter(pPlayer->GetPosition());
}
