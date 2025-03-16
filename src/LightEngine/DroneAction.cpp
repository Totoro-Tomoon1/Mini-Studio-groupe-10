#include "DroneAction.h"
#include <iostream>

void DroneAction_Idle::OnStart(Drone* pDrone)
{
	std::cout << "Idle" << std::endl;
}

void DroneAction_Moving::OnStart(Drone* pDrone)
{
	std::cout << "Moving" << std::endl;
}

void DroneAction_Shoot::OnStart(Drone* pDrone)
{
	std::cout << "Shoot" << std::endl;

	//Init des timers 
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

void DroneAction_Hacking::OnStart(Drone* pDrone)
{
	std::cout << "Hacking" << std::endl;

	mHackingTime = 3.f;
	mHackingProcess = 0.f;
}

void DroneAction_Hacking::OnUpdate(Drone* pDrone)
{
	float dt = GameManager::Get()->GetDeltaTime();

	mHackingProcess += dt;

	if (mHackingProcess > mHackingTime)
		std::cout << "Hacked !" << std::endl;
}

void DroneAction_Hacking::OnEnd(Drone* pDrone)
{
	if (mHackingProcess < mHackingTime)
		std::cout << "Hacking canceled ! " << std::endl;
}
