#include "GameManager.h"
#include "AssetManager.h"
#include "PlatFormerScene.h"
#include "Entity.h"
#include "Debug.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "Camera.h"

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;
	mAssetManager = new AssetManager();
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mpWindow;
	delete mpScene;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mClearColor = clearColor;
}

void GameManager::SetCamera(Camera& camera)
{
	cam = &camera;
	mpWindow->setView(cam->GetView());
}

void GameManager::DestroyAllEntities()
{
	for (auto it = mEntities.begin(); it != mEntities.end(); )
	{
		delete* it;        
		it = mEntities.erase(it);  
	}
}

void GameManager::Run()
{
	if (mpWindow == nullptr) 
	{
		CreateWindow(1280, 720, "Default window");
	}

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	_ASSERT(mpScene != nullptr);

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput();

		Update();
		
		Draw();
	}
}

void GameManager::HandleInput()
{
	sf::Event event;
	while (mpWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mpWindow->close();
		}

		mpScene->OnEvent(event);
	}
}

void GameManager::Update() 
{
	mpScene->OnUpdate();

    //Update
    for (auto it = mEntities.begin(); it != mEntities.end(); )
    {
		Entity* entity = *it;

        entity->Update();

        if (entity->ToDestroy() == false)
        {
            ++it;
            continue;
        }

        mEntitiesToDestroy.push_back(entity);
        it = mEntities.erase(it);
    }

	mAccumulatedDt += mDeltaTime;
	while (mAccumulatedDt >= FIXED_DT)
	{
		FixedUpdate();
		mAccumulatedDt -= FIXED_DT;
	}

	mpScene->OnLateUpdate();

	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it) 
	{
		delete *it;
	}

    mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}

	mEntitiesToAdd.clear();
}


void GameManager::FixedUpdate()
{
	for (Entity* entity : mEntities)
	{
		entity->FixedUpdate(FIXED_DT);
	}

 	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;

		for (; it2 != mEntities.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			if (entity->IsTag(otherEntity->GetTag()))
				continue;
			
			if (entity->IsTag(PlatFormerScene::Tag::GROUND) && (otherEntity->IsTag(PlatFormerScene::Tag::HACKING_ZONE) || otherEntity->IsTag(PlatFormerScene::Tag::Damagezone) || otherEntity->IsTag(PlatFormerScene::Tag::Fallzone) || otherEntity->IsTag(PlatFormerScene::Tag::ACTIVATE_ZONE)))
				continue;

			if (entity->IsColliding(otherEntity))
			{
				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);

				if (entity->IsRigidBody() && otherEntity->IsRigidBody())
					entity->Repulse(otherEntity);
			}
		}
	}
}

void GameManager::Draw()
{
	mpWindow->setView(cam->GetView());

	mpWindow->clear(mClearColor);

	mpScene->Draw(*mpWindow);
	
	for (Entity* entity : mEntities)
	{
		if (entity->ToDraw)
		{
			mpWindow->draw(*entity->GetShape());
		}
	}
	
	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}