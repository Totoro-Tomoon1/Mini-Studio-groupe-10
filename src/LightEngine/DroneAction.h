#pragma once

#include "Action.h"
#include "Drone.h"

class DroneAction_Idle : public Action<Drone>
{
public:
	void OnStart(Drone* pDrone) override;
	void OnUpdate(Drone* pDrone) override {}
	void OnEnd(Drone* pDrone) override {}
};

class DroneAction_Moving : public Action<Drone>
{
public:
	void OnStart(Drone* pDrone) override;
	void OnUpdate(Drone* pDrone) override {}
	void OnEnd(Drone* pDrone) override {}
};

class DroneAction_Attack : public Action<Drone>
{
public:
	void OnStart(Drone* pDrone) override;
	void OnUpdate(Drone* pDrone) override {}
	void OnEnd(Drone* pDrone) override {}

};

