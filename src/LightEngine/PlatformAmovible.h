#pragma once

#include "Platform.h"
class PlatformAmovible : public Platform
{
private:
	bool mActive = false;
	bool mIsMoving = false;
public:

	void OnUpdate() override;
	void OnCollision(Entity* other) override;
	bool IsActive();
	void Move(int x, int y, float speed);

};

