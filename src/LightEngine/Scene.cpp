#include "Scene.h"

#include "GameManager.h"
#include "Camera.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

sf::View Scene::GetView()
{
	return mpGameManager->mpWindow->getView();
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}


