#pragma once

#include "Condition.h"
#include "Drone.h"

class DroneCondition_IsMoving : public Condition<Drone>
{
public:
	bool OnTest(Drone* owner) override;
};

class DroneCondition_IsShooting : public Condition<Drone>
{
public:
	bool OnTest(Drone* owner) override;
};

class DroneCondition_TryHacking : public Condition<Drone>
{
public:
	bool OnTest(Drone* owner) override;
};

class DroneCondition_CanHack : public Condition<Drone>
{
public:
	bool OnTest(Drone* owner) override;
};