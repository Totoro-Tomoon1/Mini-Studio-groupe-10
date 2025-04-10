#include "PlatFormerScene.h"

#include "Player.h"
#include "Drone.h"
#include "DummyEntity.h"
#include "Platform.h"
#include "PlatformAmovible.h"
#include "Debug.h"
#include "Music.h"
#include "Sound.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Chest.h"
#include <iostream>
#include "Key.h"
#include <fstream>
#include "ParallaxLayer.h"
#include "ParallaxManager.h"

#include "Butterfly.h"

#define Butterfly_Path "../../../res/MODELSHEET_PAPILLON.png"

void PlatFormerScene::OnInitialize()
{
	mMusic = new Music();

	mMusic->Load("../../../res/Test solarpunk2.wav");
	mMusic->Play();

	mSound = new Sound();

	mSound->Load("../../../res/test.wav");
	//mSound->Play();

	mButterfly = new Burrefly();
	mButterfly->SetTexture();

	if (!backgroundTexture1->loadFromFile("../../../res/background/Fond.png") ||
		!backgroundTexture2->loadFromFile("../../../res/background/4e_plan.png") ||
		!backgroundTexture3->loadFromFile("../../../res/background/3e_plan.png") ||
		!backgroundTexture4->loadFromFile("../../../res/background/2e_plan.png") ||
		!backgroundTexture5->loadFromFile("../../../res/background/1er_plan.png"))
	{

		std::cout << "Erreur de chargement des fonds d'ecrans." << std::endl;
	}

	fpsCounter.loadFont();

	GenerateMap();

	CreateBackGround();
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	if (sf::Joystick::isButtonPressed(0, 3) && !UpPressed && mDrone->GetIsUnlocked())
	{
		UpPressed = true;

		playerSelected = !playerSelected;
		if (playerSelected)
		{
			mDrone->Undisplay();
			mPlayer->ActivateInput();
			mDrone->ResetmDepl();
			mDrone->DesactivateInput();
		}
		else
		{
			mDrone->Display(mPlayer->GetPosition());
			mPlayer->DesactivateInput();
			mPlayer->ResetmDepl();
			mDrone->ActivateInput();
		}
	}

	else if (!sf::Joystick::isButtonPressed(0, 3))
	{
		UpPressed = false;
	}

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
	mButterfly->Update(GetDeltaTime());

	sf::Vector2f fpsPos = { mCamera.GetView().getCenter().x - 640.f, mCamera.GetView().getCenter().y - 360.f };
	fpsCounter.update(fpsPos);

	if (mPlayer->GetHP() <= 0 || mDrone->GetHP() <= 0)
	{
		GameManager::Get()->DestroyAllEntities();
		GenerateMap();
		Reset();
	}
}

void PlatFormerScene::OnLateUpdate()
{
	mCamera.GetView().setCenter(mPlayer->GetPosition(0.5f, 0.5f));
}

void PlatFormerScene::Draw(sf::RenderWindow& pRenderWindow)
{
	mParallaxManager->Draw(pRenderWindow);
	mButterfly->Draw(pRenderWindow);
	mButterfly->SetView(GetView());
	fpsCounter.draw(pRenderWindow);
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

void PlatFormerScene::Reset()
{
	mParallaxManager->SetPlayer(mPlayer);
	playerSelected = true;
	UpPressed = false;
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
	std::vector<std::tuple<int, int, int>> ground;
	std::vector<std::tuple<int, int, int>> damageZone;
	std::vector<std::tuple<int, int, int>> fallZone;
	std::vector<std::tuple<int, int, int>> hackingZone;
	std::vector<std::tuple<int, int, int>> activatingZone;
	std::vector<std::tuple<int, int, int>> platformAmovible;

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
			else if (line[i] == 'c' || line[i] == 'x')
			{
				int startX = i;
				size_t count = 1;
				size_t j = i + 1;

				while (j < line.size() && (line[j] == 'x' || line[j] == 'c')) 
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
				while (j < line.size() && line[j] == 'h')
				{
					count++;
					j++;
				}

				hackingZone.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'a')
			{
				size_t count = 1;
				size_t j = i + 1;
				while (j < line.size() && line[j] == 'a')
				{
					count++;
					j++;
				}

				activatingZone.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'm')
			{
				size_t count = 1;
				size_t j = i + 1;
				while (j < line.size() && line[j] == 'm')
				{
					count++;
					j++;
				}

				platformAmovible.push_back(std::make_tuple(i, count, lineNumber));

				i = j;
			}
			else if (line[i] == 'p')
			{
				mPlayer = CreateRectangleEntity<Player>(sf::Vector2f(40/1.5f, 120/1.5f), sf::Color::White);
				mPlayer->SetPosition(i * 20, lineNumber * 20);
				mPlayer->SetToDraw(true);
				mPlayer->ActivateInput();
				mCamera.SetPosition(mPlayer->GetPosition());
				GameManager::Get()->SetCamera(mCamera);
				i++;
			}
			else if (line[i] == 'd')
			{
				mDrone = CreateRectangleEntity<Drone>(sf::Vector2f(50, 50), sf::Color::White);
				mDrone->Display(sf::Vector2f(i * 20, lineNumber * 20));
				i++;
			}
			else if (line[i] == 'e')
			{
				Enemy1* pEnemy = CreateRectangleEntity<Enemy1>(sf::Vector2f(40, 40), sf::Color::White);
				pEnemy->SetPosition(i * 20, lineNumber * 20);
				pEnemy->SetGravity(true);
				i++;
			}
			else if (line[i] == 'g')
			{
				Enemy2* pEnemy = CreateRectangleEntity<Enemy2>(sf::Vector2f(40, 40), sf::Color::White);
				pEnemy->SetPosition(i * 20, lineNumber * 20);
				i++;
			}
			else if (line[i] == 'b')
			{
				Boss * pBoss = CreateRectangleEntity<Boss>(sf::Vector2f(150, 150), sf::Color::White);
				pBoss->SetPosition(i * 20, lineNumber * 20);
				pBoss->SetDroneTarget(mDrone);
				i++;
		    }
			else if (line[i] == 'k')
			{
				Key* pKey = CreateRectangleEntity<Key>(sf::Vector2f(31, 79), sf::Color::Yellow);
				pKey->SetPosition(i * 20, lineNumber * 20);
				pKey->SetTag(Tag::KEY);
				i++;
				}

			else if (line[i] == 't')
			{
				Chest* pChest = CreateRectangleEntity<Chest>(sf::Vector2f(60, 60), sf::Color::White);
				pChest->SetPosition(i * 20, lineNumber * 20);
				pChest->SetTag(Tag::CHEST);
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

	for (int i = 0; i < ground.size(); i++) {
		int startX = std::get<0>(ground[i]);
		int totalLength = std::get<1>(ground[i]);
		int entityLine = std::get<2>(ground[i]);

		if (i > 0) {
			if (startX == std::get<0>(ground[i - 1]) && totalLength == std::get<1>(ground[i - 1])) {
				continue;
			}
		}

		int countLigne = 1;
		int j = i + 1;
		while (j < ground.size() && startX == std::get<0>(ground[j]) && totalLength == std::get<1>(ground[j])) {
			j++;
			countLigne++;
		}

		Platform* pGround = CreateRectangleEntity<Platform>(sf::Vector2f(totalLength * 20, 40 * countLigne), sf::Color::White);
		pGround->SetPosition(startX * 20, entityLine * 20);
		pGround->SetRigidBody(true);
		pGround->SetStatic(true);
		pGround->SetTag(Tag::GROUND);
		pGround->SetToDraw(true);

		bool hasXAbove = false;
		for (const auto& elem : ground) {
			int aboveX = std::get<0>(elem);
			int aboveLength = std::get<1>(elem);
			int aboveLine = std::get<2>(elem);

			if (aboveX == startX && aboveLength == totalLength && aboveLine == entityLine - 1) {
				hasXAbove = true;
				break;
			}
		}

		if (hasXAbove) {
			pGround->SetTexture(2); 
		}
		else {
			pGround->SetTexture(3); 
		}
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

		int countLigne = 1;
		int j = i + 1;
		while (j < damageZone.size() && start == std::get<0>(damageZone[j]) && totalLenght == std::get<1>(damageZone[j]))
		{
			j++;
			countLigne++;
		}

		Entity* pDamage = CreateRectangleEntity<Platform>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::White);
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

		int countLigne = 1;
		int j = i + 1;
		while (j < fallZone.size() && start == std::get<0>(fallZone[j]) && totalLenght == std::get<1>(fallZone[j]))
		{
			j++;
			countLigne++;
		}

		Entity* pFall = CreateRectangleEntity<Platform>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::White);
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

		int countLigne = 1;
		int j = i + 1;
		while (j < activatingZone.size() && start == std::get<0>(activatingZone[j]) && totalLenght == std::get<1>(activatingZone[j]))
		{
			j++;
			countLigne++;
		}

		Entity* pActivating = CreateRectangleEntity<PlatformAmovible>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::Black);
		pActivating->SetStatic(true);
		pActivating->SetRigidBody(true);                                       
		pActivating->SetPosition(start * 20, entityLine * 20);
		pActivating->SetTag(Tag::ACTIVATE_ZONE);
	}

	for (int i = 0; i < platformAmovible.size(); i++)
	{
		int start = std::get<0>(platformAmovible[i]);
		int totalLenght = std::get<1>(platformAmovible[i]);
		int entityLine = std::get<2>(platformAmovible[i]);

		if (i > 0)
		{
			if (start == std::get<0>(platformAmovible[i - 1]) && totalLenght == std::get<1>(platformAmovible[i - 1]))
				continue;
		}

		int countLigne = 1;
		int j = i + 1;
		while (j < platformAmovible.size() && start == std::get<0>(platformAmovible[j]) && totalLenght == std::get<1>(platformAmovible[j]))
		{
			j++;
			countLigne++;
		}

		PlatformAmovible* pActivating = CreateRectangleEntity<PlatformAmovible>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::Black);
		pActivating->SetPosition(start * 20, entityLine * 20);
		pActivating->SetRigidBody(true);
		pActivating->SetTag(Tag::Amovible);
	}

	for (int i = 0; i < hackingZone.size(); i++)
	{
		int start = std::get<0>(hackingZone[i]);
		int totalLenght = std::get<1>(hackingZone[i]);
		int entityLine = std::get<2>(hackingZone[i]);

		if (i > 0)
		{
			if (start == std::get<0>(hackingZone[i - 1]) && totalLenght == std::get<1>(hackingZone[i - 1]))
				continue;
		}

		int countLigne = 1;
		int j = i + 1;
		while (j < hackingZone.size() && start == std::get<0>(hackingZone[j]) && totalLenght == std::get<1>(hackingZone[j]))
		{
			j++;
			countLigne++;
		}

		PlatformAmovible* pActivating = CreateRectangleEntity<PlatformAmovible>(sf::Vector2f(totalLenght * 20, 20 * countLigne), sf::Color::Black);
		pActivating->SetPosition(start * 20, entityLine * 20);
		pActivating->SetRigidBody(true);
		pActivating->SetStatic(true);
		pActivating->SetTag(Tag::HACKING_ZONE);
	}
}