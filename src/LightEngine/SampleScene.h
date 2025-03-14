#pragma once

#include "Scene.h"

class Player;
class Entity;

class SampleScene : public Scene
{
	Entity* pEntity1;

	Entity* pEntitySelected;

private:
	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


