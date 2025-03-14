#include "PlatFormerScene.h"

#include "Player.h"
#include "DummyEntity.h"
#include "Debug.h"

#include <iostream>

#include <fstream>

void PlatFormerScene::OnInitialize()
{
	/*pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(640, 200), sf::Color::Red);
	pGround->SetPosition(0, 600);
	pGround->SetRigidBody(true);
	pGround->SetStatic(true);
	pGround->SetTag(Tag::GROUND);

	pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(640, 200), sf::Color::Red);
	pGround->SetPosition(700, 500);
	pGround->SetRigidBody(true);
	pGround->SetStatic(true);
	pGround->SetTag(Tag::GROUND);

	pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(400, 50), sf::Color::Red);
	pGround->SetPosition(0, 400);
	pGround->SetRigidBody(true);
	pGround->SetStatic(true);
	pGround->SetTag(Tag::GROUND);

	pPlayer = CreateRectangleEntity<Player>(sf::Vector2f(100,200), sf::Color::Green);*/

	std::ifstream file("../../../res/Level-Editor.txt");
	if (!file.is_open())
	{
		std::cerr << "Erreur : Impossible d'ouvrir le fichier " << "../../../res/Level-Editor.txt" << std::endl;
		return;
	}

	int lineNumber = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << "Ligne lue: " << line << std::endl;

		size_t i = 0;
		while (i < line.size()) {
			if (line[i] == 'x') {
				// Trouv� un 'x', maintenant compter les 'x' suivants
				size_t count = 0;

				// Compter les 'x' derri�re le premier trouv�
				size_t j = i + 1;
				while (j < line.size() && line[j] == 'x') {
					count++;
					j++;
				}

				// Afficher combien de 'x' suivent
				std::cout << "Nombre de 'x' apr�s l'index " << i << ": " << count << std::endl;

				pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(count * 20, 20), sf::Color::Red);
				pGround->SetPosition(i * 20, lineNumber * 20);
				pGround->SetRigidBody(true);
				pGround->SetStatic(true);
				pGround->SetTag(Tag::GROUND);

				// Passer apr�s le dernier 'x' trouv�
				i = j;
			}
			else if (line[i] == 'p')
			{
				std::cout << "p a la ligne :" << lineNumber * 20 << "    et a l'index : " << i * 20 << std::endl;
				pPlayer = CreateRectangleEntity<Player>(sf::Vector2f(100, 200), sf::Color::White);
				pPlayer->SetPosition(i * 20, lineNumber * 20);
				mCamera.SetPosition(pPlayer->GetPosition());
				GameManager::Get()->SetCamera(mCamera);
				i++;
			}
			else {
				// Si ce n'est pas un 'x', simplement avancer
				i++;
			}
		}
		lineNumber++;
	}

	file.close();
	
	
	
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::JoystickButtonPressed)
		return;

	std::cout << "Mannette connecte" << std::endl;


}

void PlatFormerScene::OnLateUpdate()
{
	//std::cout << pPlayer->GetPosition().y << "\t";
	mCamera.GetView().setCenter(pPlayer->GetPosition(0.5f, 0.5f));
}
