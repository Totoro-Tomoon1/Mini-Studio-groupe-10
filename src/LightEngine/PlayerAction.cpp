#include "PlayerAction.h"
#include "Player.h"

#include "GameManager.h"
#include "Scene.h"
#include <iostream>

void PlayerAction_Idle::OnStart(Player* pPlayer)
{
	std::cout << "Idle" << std::endl;
	pPlayer->mPlayerAnimation->SetNewY(0);
}

void PlayerAction_Moving::OnStart(Player* pPlayer)
{
	std::cout << "Moving" << std::endl;
	pPlayer->mPlayerAnimation->SetNewY(0);
}

void PlayerAction_Jump::OnStart(Player* pPlayer)
{
	std::cout << "Jump" << std::endl;
	pPlayer->mPlayerAnimation->SetNewY(261);
}

void PlayerAction_Jump::OnUpdate(Player* pPlayer)
{

}

void PlayerAction_Fall::OnStart(Player* pPlayer)
{
	std::cout << "Fall" << std::endl;
}