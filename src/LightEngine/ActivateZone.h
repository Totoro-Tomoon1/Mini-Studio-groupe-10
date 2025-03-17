#pragma once

#include "Platform.h"
class ActivateZone : public Platform
{
public:

	void OnCollision(Entity* other) override;
	bool IsActive();

};
