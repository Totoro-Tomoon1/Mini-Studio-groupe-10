#pragma once

#include "Platform.h"
class PlatformAmovible : public Platform
{
public:

	void OnCollision(Entity* other) override;
	bool IsActive();

};

