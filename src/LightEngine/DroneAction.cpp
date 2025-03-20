#include "DroneAction.h"
#include <iostream>

void DroneAction_Idle::OnStart(Drone* pDrone)
{
}

void DroneAction_Moving::OnStart(Drone* pDrone)
{
}

void DroneAction_Shoot::OnStart(Drone* pDrone)
{
	mShootInterval = 0.3f;
	mLastShotTime = 0.f;

	pDrone->Shoot(GameManager::Get()->GetDeltaTime());
}

void DroneAction_Shoot::OnUpdate(Drone* pDrone)
{
	float dt = GameManager::Get()->GetDeltaTime();
	mLastShotTime += dt;

	if (mLastShotTime < mShootInterval)
		return;

	mLastShotTime = 0.f;
	pDrone->Shoot(dt);
}