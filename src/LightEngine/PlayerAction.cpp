#include "PlayerAction.h"
#include "Player.h"

#include "GameManager.h"
#include "Scene.h"
#include <iostream>

void PlayerAction_Idle::OnStart(Player* pPlayer)
{
	std::cout << "Idle" << std::endl;
}

void PlayerAction_Moving::OnStart(Player* pPlayer)
{
	std::cout << "Moving" << std::endl;
}

void PlayerAction_Jump::OnStart(Player* pPlayer)
{
	std::cout << "Jump" << std::endl;
}

void PlayerAction_Jump::OnUpdate(Player* pPlayer)
{

}

void PlayerAction_Fall::OnStart(Player* pPlayer)
{
	std::cout << "Fall" << std::endl;
}