#pragma once
#include "Entity.h"

class Platform : public Entity
{
public:
 virtual void OnCollision(Entity* other) override;
};

