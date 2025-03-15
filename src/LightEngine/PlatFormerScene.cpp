#include "PlatFormerScene.h"

#include "Player.h"
#include "DummyEntity.h"
#include "Debug.h"
#include "Music.h"
#include "Sound.h"

#include <iostream>

#include <fstream>
#include "ParallaxLayer.h"
#include "ParallaxManager.h"

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


	mMusic = new Music();

	mMusic->Load("../../../res/blood.wav");
	//mMusic->Play();

	mSound = new Sound();

	mSound->Load("../../../res/test.wav");
	//mSound->Play();

	std::ifstream file("../../../res/Level-Editor.txt");
	if (!file.is_open())
	{
		std::cerr << "Erreur : Impossible d'ouvrir le fichier " << "../../../res/Level-Editor.txt" << std::endl;
		return;
	}

	int lineNumber = 0;
	std::vector<std::tuple<int, int, int>> entities;  // (startX, totalLength, lineNumber)

	std::string line;
	while (std::getline(file, line))
	{
		std::cout << "Ligne lue: " << line << std::endl;
		size_t i = 0;
		while (i < line.size())
		{
			if (line[i] == 'x')
			{
				int startX = i;
				size_t count = 1;
				size_t j = i + 1;
				while (j < line.size() && line[j] == 'x')
				{
					count++;
					j++;
				}

				// Enregistrer l'entité (startX, totalLength, lineNumber)
				entities.push_back(std::make_tuple(startX, count, lineNumber));

				// Afficher combien de 'x' suivent
				std::cout << "Nombre de 'x' après l'index " << i << ": " << count << std::endl;

				// Passer après le dernier 'x' trouvé
				i = j;
			}
			else if (line[i] == 'p')
			{
				std::cout << "p à la ligne :" << lineNumber * 20 << "    et à l'index : " << i * 20 << std::endl;
				mPlayer = CreateRectangleEntity<Player>(sf::Vector2f(160, 130), sf::Color::White);
				mPlayer->SetPosition(i * 20, lineNumber * 20);
				mCamera.SetPosition(mPlayer->GetPosition());
				GameManager::Get()->SetCamera(mCamera);
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

	// Créer les entités à partir des données collectées
	for (const auto& entity : entities)
	{
		int startX = std::get<0>(entity);
		int totalLength = std::get<1>(entity);
		int entityLine = std::get<2>(entity);

		// Créer l'entité
		pGround = CreateRectangleEntity<DummyEntity>(sf::Vector2f(totalLength * 20, 20), sf::Color::Red);
		pGround->SetPosition(startX * 20, entityLine * 20);
		pGround->SetRigidBody(true);
		pGround->SetStatic(true);
		pGround->SetTag(Tag::GROUND);
	}

	
	//Creation du fond
	CreateBackGround();
	
}

void PlatFormerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::JoystickButtonPressed)
		return;

	std::cout << "Mannette connecte" << std::endl;


}

void PlatFormerScene::OnUpdate()
{
	mParallaxManager->Update(GetDeltaTime());
}

void PlatFormerScene::OnLateUpdate()
{
	//std::cout << pPlayer->GetPosition().y << "\t";
	mCamera.GetView().setCenter(mPlayer->GetPosition(0.5f, 0.5f));
}

void PlatFormerScene::Draw(sf::RenderWindow& pRenderWindow)
{
	mParallaxManager->Draw(pRenderWindow);
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
	sf::Texture* backgroundTexture6 = new sf::Texture;
	sf::Texture* backgroundTexture7 = new sf::Texture;
		
	if (!backgroundTexture1->loadFromFile("../../../res/layers/sky.png") ||
		!backgroundTexture2->loadFromFile("../../../res/layers/clouds_1.png") ||
		!backgroundTexture3->loadFromFile("../../../res/layers/clouds_2.png") ||
		!backgroundTexture4->loadFromFile("../../../res/layers/rocks_1.png") ||
		!backgroundTexture5->loadFromFile("../../../res/layers/clouds_3.png") ||
		!backgroundTexture6->loadFromFile("../../../res/layers/rocks_2.png") ||
		!backgroundTexture7->loadFromFile("../../../res/layers/clouds_4.png"))
	{

		std::cout << "Erreur de chargement des fonds d'ecrans." << std::endl;
	}

	ParallaxLayer background1(backgroundTexture1, 0.2f);
	ParallaxLayer background2(backgroundTexture2, 0.25f);
	ParallaxLayer background3(backgroundTexture3, 0.3f);
	ParallaxLayer background4(backgroundTexture4, 0.45f);
	ParallaxLayer background5(backgroundTexture5, 0.4f);
	ParallaxLayer background6(backgroundTexture6, 0.45f);
	ParallaxLayer background7(backgroundTexture7, 0.5f);

	mParallaxManager->AddLayers(background1);
	mParallaxManager->AddLayers(background2);
	mParallaxManager->AddLayers(background3);
	mParallaxManager->AddLayers(background4);
	mParallaxManager->AddLayers(background5);
	mParallaxManager->AddLayers(background6);
	mParallaxManager->AddLayers(background7);
}