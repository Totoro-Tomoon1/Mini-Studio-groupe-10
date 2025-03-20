#pragma once
#include "Entity.h"

class Animation;

class Key : public Entity
{
    Animation* mAnimation;
    sf::Texture* mTexture;

public:
    //void OnInitialize() override;
    //void OnUpdate() override;
};

