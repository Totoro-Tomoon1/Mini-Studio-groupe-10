#pragma once

#include "Scene.h"

class Player;

class SampleScene : public Scene
{
	Player* pEntity1;

	Player* pEntitySelected;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


