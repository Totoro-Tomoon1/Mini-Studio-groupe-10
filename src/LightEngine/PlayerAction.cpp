#include "PlayerAction.h"
#include "Player.h"

#include "GameManager.h"
#include "Scene.h"

//void PlayerAction_Jump::OnStart(Player* pPlayer)
//{
//	mJumpTimer = pPlayer->mJumpDuration;
//}
//
//void PlayerAction_Jump::OnUpdate(Player* pPlayer)
//{
//	mJumpTimer += GameManager::Get()->GetDeltaTime();
//
//	if (mJumpTimer < pPlayer->mJumpDuration)
//		return;
//
//	mJumpTimer -= pPlayer->mJumpDuration;
//
//	Scene* pScene = pPlayer->GetScene<Scene>();
//
//	const sf::Vector2f& position = pPlayer->GetPosition();
//}
