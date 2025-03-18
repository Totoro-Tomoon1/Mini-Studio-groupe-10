#include "PlatFormerScene.h"


#include "Player.h"
#include "Drone.h"
#include "DummyEntity.h"
#include "Platform.h"
#include "PlatformAmovible.h"
#include "ActivateZone.h"
#include "Debug.h"
#include "Music.h"
#include "Sound.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Boss.h"
#include <iostream>

#include <fstream>
#include "ParallaxLayer.h"
#include "ParallaxManager.h"
#include "DamageZone.h"
#include "FallZone.h"

void PlatFormerScene::OnInitialize()
{
	mMusic = new Music();

	mMusic->Load("../../../res/blood.wav");
	//mMusic->Play();

	mSound = new Sound();

	mSound->Load("../../../res/test.wav");
	//mSound->Play();

	mDrone = CreateRectangleEntity<Drone>(sf::Vector2f(50, 50), sf::Color::Blue);
	mDrone->Undisplay();

	GenerateMap();
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	//if (event.type == sf::Event::EventType::JoystickButtonPressed)
		//std::cout << "Mannette connecte" << std::endl;

	/*if (event.type == sf::Event::KeyPressed)
	{*/
	
		if (sf::Joystick::isButtonPressed(0, 3) && !UpPressed && mDrone->GetIsUnlocked())
		{
			UpPressed = true;
			std::cout << UpPressed << std::endl;
			playerSelected = !playerSelected;
			if (playerSelected)
			{
				mDrone->Undisplay();
				mPlayer->ActivateInput();
				mDrone->ResetmDepl();
				mDrone->DesactivateInput();
				//mPlayer->ChangeStatic(false);
			}
			else
			{
				mDrone->Display(mPlayer->GetPosition());
				mPlayer->DesactivateInput();
				mPlayer->ResetmDepl();
				mDrone->ActivateInput();
				//mPlayer->ChangeStatic(true);
			}
		}

		else if (!sf::Joystick::isButtonPressed(0, 3))
		{
			UpPressed = false;
		}
	//}

	if (playerSelected)
	{
		mPlayer->Input();
	}
	else
	{
		mDrone->Input();
	}
}

void PlatFormerScene::OnUpdate()
{
	mParallaxManager->Update(GetDeltaTime());

	if (mPlayer->GetHP() <= 0)
	{
		GameManager::Get()->DestroyAllEntities();
		GenerateMap();
	}
}

void PlatFormerScene::OnLateUpdate()
{
	mCamera.GetView().setCenter(mPlayer->GetPosition(0.5f, 0.5f));
}

void PlatFormerScene::Draw(sf::RenderWindow& pRenderWindow)
{
	mParallaxManager->Draw(pRenderWindow);
}

Player* PlatFormerScene::GetPlayer()
{
	return mPlayer;
}

Drone* PlatFormerScene::GetDrone()
{
	return mDrone;
}

void PlatFormerScene::CreateBackGround()
{
	mParallaxManager = new ParallaxManager();
	mParallaxManager->SetPlayer(mPlayer);

	sf::Texture* backgroundTexture1 = new sf::Texture;
	sf::Texture* backgroundTexture2 = new sf::Texture;
	sf::Texture* backgroundTexture3 = new sf::Texture;
	sf::Texture* backgroundTexture4 = new sf::Texture;
	sf::Texture* backgroundTexture5 = new sf::Texture;
		
	if (!backgroundTexture1->loadFromFile("../../../res/background/Fond.png") ||
		!backgroundTexture2->loadFromFile("../../../res/background/4e_plan.png") ||
		!backgroundTexture3->loadFromFile("../../../res/background/3e_plan.png") ||
		!backgroundTexture4->loadFromFile("../../../res/background/2e_plan.png") ||
		!backgroundTexture5->loadFromFile("../../../res/background/1er_plan.png"))
	{

		std::cout << "Erreur de chargement des fonds d'ecrans." << std::endl;
	}

	ParallaxLayer background1(backgroundTexture1, 0.01f);
	ParallaxLayer background2(backgroundTexture2, 0.1f);
	ParallaxLayer background3(backgroundTexture3, 0.2f);
	ParallaxLayer background4(backgroundTexture4, 0.3f);
	ParallaxLayer background5(backgroundTexture5, 0.4f);

	mParallaxManager->AddLayers(background1);
	mParallaxManager->AddLayers(background2);
	mParallaxManager->AddLayers(background3);
	mParallaxManager->AddLayers(background4);
	mParallaxManager->AddLayers(background5);
}

void PlatFormerScene::GenerateMap()
{
	std::ifstream file("../../../res/Level-Editor.txt");
	if (!file.is_open())
	{
		std::cerr << "Erreur : Impossible d'ouvrir le fichier " << "../../../res/Level-Editor.txt" << std::endl;
		return;
	}

	int lineNumber = 0;
	std::vector<std::tuple<int, int, int>> ground;// (startX, totalLength, lineNumber)
	std::vector<std::tuple<int, int, int>> damageZone;
	std::vector<std::tuple<int, int, int>> fallZone;
	std::vector<std::tuple<int, int, int>> hackingZone;
	std::vector<std::tuple<int, int, int>> activatingZone;

	std::string line;
	while (std::getline(file, line))
	{
		size_t i = 0;
		while (i < line.size())
		{
			if (line[i] == '-')
			{
				i++;
			}
			else if (line[i] == 'x')
			{
				int startX = i;
				size_t count = 1;
				size_t j = i + 1;
				while (j < line.size() && line[j] == 'x')
				{
					count++;
					j++;
				}

				ground.push_back(std::make_tuple(startX, count, lineNumber));

				i = j;
			}
			else if (line[i] == 's')
			{
				size_t count = 1;
				size_t j = i + 1;
				while (j < line.size() && line[j] == 's')
				{
					count++;
					j++;
				}

				damageZone.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'f')
			{
				size_t count = 1;
				size_t j = i + 1;
				while (j < line.size() && line[j] == 'f')
				{
					count++;
					j++;
				}

				fallZone.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'h')
			{
				size_t count = 1;
				size_t j = i + 1;
				std::cout << i << std::endl;
				while (j < line.size() && line[j] == 'h')
				{
					//std::cout << "beug " << j << std::endl;
					count++;
					j++;
				}

				// Enregistrer l'entité (startX, totalLength, lineNumber)
				hackingZone.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'a')
			{
				size_t count = 1;
				size_t j = i + 1;
				std::cout << i << std::endl;
				while (j < line.size() && line[j] == 'a')
				{
					//std::cout << "beug " << j << std::endl;
					count++;
					j++;
				}

				// Enregistrer l'entité (startX, totalLength, lineNumber)
				activatingZone.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'p')
			{
				mPlayer = CreateRectangleEntity<Player>(sf::Vector2f(60 / 2, 120 / 2), sf::Color::White);
				mPlayer->SetPosition(i * 20, lineNumber * 20);
				mPlayer->SetToDraw(true);
				mPlayer->ActivateInput();
				mCamera.SetPosition(mPlayer->GetPosition());
				GameManager::Get()->SetCamera(mCamera);
				i++;
			}
			else if (line[i] == 'd')
			{
				//mDrone->SetPosition(i * 20, lineNumber * 20);
				mDrone->Display(sf::Vector2f(i * 20, lineNumber * 20));
				i++;
			}
			else if (line[i] == 'e')
			{
				Enemy1* pEnemy = CreateRectangleEntity<Enemy1>(sf::Vector2f(150, 150), sf::Color::Magenta);
				pEnemy->SetPosition(i * 20, lineNumber * 20);
				//pEnemy->SetTextureAndAnim();
				i++;
			}
			else if (line[i] == 'g')
			{
				Enemy1* pEnemy = CreateRectangleEntity<Enemy1>(sf::Vector2f(150, 150), sf::Color::Black);
				pEnemy->SetPosition(i * 20, lineNumber * 20);
				//pEnemy->SetTextureAndAnim();
				//pEnemy->SetGravity(false);
				i++;
			}
			else if (line[i] == 'b')
			{
				Boss * pBoss = CreateRectangleEntity<Boss>(sf::Vector2f(150, 150), sf::Color::Green);
				pBoss->SetPosition(i * 20, lineNumber * 20);
				pBoss->SetDroneTarget(mDrone);
				i++;
		    }
			else
			{
				i++;
			}
		}
		lineNumber++;
	}

	file.close();

	for (int i = 0; i < ground.size(); i++)
	{
		int startX = std::get<0>(ground[i]);
		int totalLength = std::get<1>(ground[i]);
		int entityLine = std::get<2>(ground[i]);

		if (i > 0)
		{
			if (startX == std::get<0>(ground[i - 1]) && totalLength == std::get<1>(ground[i - 1]))
				continue;
		}
			//pas de ligne au dessus identique

		int countLigne = 1;
		int j = i + 1;
		while (j < ground.size() && startX == std::get<0>(ground[j]) && totalLength == std::get<1>(ground[j]))
		{
			j++;
			countLigne++;
		}
		
		pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(totalLength * 20, 20 * countLigne), sf::Color::Red);
		pGround->SetPosition(startX * 20, entityLine * 20);
		pGround->SetRigidBody(true);
		pGround->SetStatic(true);
		pGround->SetTag(Tag::GROUND);
	}

	for (int i = 0; i < damageZone.size(); i++)
	{
		int start = std::get<0>(damageZone[i]);
		int totalLenght = std::get<1>(damageZone[i]);
		int entityLine = std::get<2>(damageZone[i]);

		if (i > 0)
		{
			if (start == std::get<0>(damageZone[i - 1]) && totalLenght == std::get<1>(damageZone[i - 1]))
				continue;
		}
		//pas de ligne au dessus identique

		int countLigne = 1;
		int j = i + 1;
		while (j < damageZone.size() && start == std::get<0>(damageZone[j]) && totalLenght == std::get<1>(damageZone[j]))
		{
			j++;
			countLigne++;
		}

		Entity* pDamage = CreateRectangleEntity<DamageZone>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::White);
		pDamage->SetPosition(start * 20, entityLine * 20);
		pDamage->SetToDraw(false);
		pDamage->SetTag(Tag::Damagezone);
	}

	for (int i = 0; i < fallZone.size(); i++)
	{
		int start = std::get<0>(fallZone[i]);
		int totalLenght = std::get<1>(fallZone[i]);
		int entityLine = std::get<2>(fallZone[i]);

		if (i > 0)
		{
			if (start == std::get<0>(fallZone[i - 1]) && totalLenght == std::get<1>(fallZone[i - 1]))
				continue;
		}
		//pas de ligne au dessus identique

		int countLigne = 1;
		int j = i + 1;
		while (j < fallZone.size() && start == std::get<0>(fallZone[j]) && totalLenght == std::get<1>(fallZone[j]))
		{
			j++;
			countLigne++;
		}

		Entity* pFall = CreateRectangleEntity<FallZone>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::White);
		pFall->SetPosition(start * 20, entityLine * 20);
		pFall->SetToDraw(false);
		pFall->SetTag(Tag::Fallzone);
	}

	for (int i = 0; i < activatingZone.size(); i++)
	{
		int start = std::get<0>(activatingZone[i]);
		int totalLenght = std::get<1>(activatingZone[i]);
		int entityLine = std::get<2>(activatingZone[i]);

		if (i > 0)
		{
			if (start == std::get<0>(activatingZone[i - 1]) && totalLenght == std::get<1>(activatingZone[i - 1]))
				continue;
		}
		//pas de ligne au dessus identique

		int countLigne = 1;
		int j = i + 1;
		while (j < activatingZone.size() && start == std::get<0>(activatingZone[j]) && totalLenght == std::get<1>(activatingZone[j]))
		{
			j++;
			countLigne++;
		}

		Entity* pActivating = CreateRectangleEntity<ActivateZone>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::Black);
		pActivating->SetPosition(start * 20, entityLine * 20);
		pActivating->SetTag(Tag::ACTIVATE_ZONE);
	}

	for (const auto& entity : hackingZone)
	{
		int start = std::get<0>(entity);
		int totalLenght = std::get<1>(entity);
		int entityLine = std::get<2>(entity);

		Entity* pHacking = CreateRectangleEntity<DummyEntity>(sf::Vector2f(totalLenght * 20, 20), sf::Color::Black);
		pHacking->SetPosition(start * 20, entityLine * 20);
		pHacking->SetToDraw(false);
		pHacking->SetTag(Tag::HACKING_ZONE);
	}

	//Creation du fond
	CreateBackGround();
}
