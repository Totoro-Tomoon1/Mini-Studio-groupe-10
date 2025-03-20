#pragma once
#include "Entity.h"

class Key : public Entity
{
    sf::Texture* mTexture;

public:
    void OnInitialize() override;
    //void OnUpdate() override;
};

