#include "Life.h"

void Life::SetLife(float maxHP)
{
	mMaxHP = maxHP;
	mCurrentHP = maxHP;
}

void Life::TakeDamage(float damage)
{
	mCurrentHP -= damage;
}

float Life::GetHP()
{
	return mCurrentHP;
}
