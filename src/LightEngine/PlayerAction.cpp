#include "PlayerAction.h"
#include "Player.h"

#include "GameManager.h"
#include "Scene.h"
#include <iostream>

void PlayerAction_Idle::OnStart(Player* pPlayer)
{
	pPlayer->mPlayerAnimation->SetNewY(0);
	pPlayer->mPlayerAnimation->SetNBFrame(4);
	pPlayer->mPlayerAnimation->SetNewXsize(40);
}

void PlayerAction_Moving::OnStart(Player* pPlayer)
{
	pPlayer->mPlayerAnimation->SetNewY(244);
	pPlayer->mPlayerAnimation->SetNBFrame(6);
	pPlayer->mPlayerAnimation->SetNewXsize(50);
}

void PlayerAction_Jump::OnStart(Player* pPlayer)
{
	pPlayer->mPlayerAnimation->SetNewY(121);
	pPlayer->mPlayerAnimation->SetNBFrame(6);
	pPlayer->mPlayerAnimation->SetNewXsize(50);

}

void PlayerAction_Jump::OnUpdate(Player* pPlayer)
{

}

void PlayerAction_Fall::OnStart(Player* pPlayer)
{
}