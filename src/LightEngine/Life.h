#pragma once

class Life
{
protected:
	float mMaxHP;
	float mCurrentHP;

public:
	void SetLife(float maxHP);

	void TakeDamage(float damage);
	float GetHP();
};