#pragma once

#include "Platform.h"
class PlatformAmovible : public Platform
{
private:
	bool mActive = false;
	bool mIsMoving = false;
	bool mIsGettingHacked = false;
public:

	void OnInitialize() override;
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
	bool IsActive();
	void IsGettingHacked();
	void Move(int x, int y, float speed);

};