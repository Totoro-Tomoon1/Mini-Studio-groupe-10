#include "ParallaxLayer.h"
#include <iostream>
#include "Player.h"

ParallaxLayer::ParallaxLayer(sf::Texture* texture, float speed)
{
    if (!texture)
    {
        std::cerr << "Erreur : texture non valide !" << std::endl;
        return;
    }

    texture->setRepeated(true);
    mImage = texture->copyToImage();

    if (mImage.getSize().x == 0 || mImage.getSize().y == 0)
    {
        std::cerr << "Erreur : l'image copi�e depuis la texture est vide !" << std::endl;
        return;
    }

    mSprite1.setTexture(*texture);
    mSprite1.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
    mSprite1.setScale(sf::Vector2f(1280.f / 1920.f * 1.1f, 720.f / 1080.f * 1.1f));

    mSprite2.setTexture(*texture);
    mSprite2.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
    mSprite2.setScale(sf::Vector2f(1280.f / 1920.f * 1.1f, 720.f / 1080.f * 1.1f));
    mSprite2.setPosition(mSprite1.getGlobalBounds().width, 0);

    mSpeed = speed;
}

void ParallaxLayer::Update(Player* player, sf::Vector2f oldPos)
{
    sf::Vector2f offset = player->GetPosition() - oldPos;
    sf::Vector2f playerPos = player->GetPosition();

    float newX = playerPos.x - player->GetScene()->GetWindowWidth() / 2;

    mSprite1.setPosition(mSprite1.getPosition().x - offset.x * mSpeed + offset.x, mSprite1.getPosition().y);
    mSprite2.setPosition(mSprite2.getPosition().x - offset.x * mSpeed + offset.x, mSprite2.getPosition().y);

    float spriteWidth = mSprite1.getGlobalBounds().width;

    if (mSprite1.getPosition().x <= newX - spriteWidth)
    {
        mSprite1.setPosition(mSprite2.getPosition().x + spriteWidth, mSprite1.getPosition().y);
    }
    else if (mSprite1.getPosition().x >= newX + spriteWidth)
    {
        mSprite1.setPosition(mSprite2.getPosition().x - spriteWidth, mSprite1.getPosition().y);
    }

    if (mSprite2.getPosition().x <= newX - spriteWidth)
    {
        mSprite2.setPosition(mSprite1.getPosition().x + spriteWidth, mSprite2.getPosition().y);
    }
    else if (mSprite2.getPosition().x >= newX + spriteWidth)
    {
        mSprite2.setPosition(mSprite1.getPosition().x - spriteWidth, mSprite2.getPosition().y);
    }
}


void ParallaxLayer::SetPosition(sf::Vector2f posPlayer)
{
    sf::FloatRect bounds = mSprite1.getGlobalBounds();
    sf::Vector2f spriteCenter(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

    mSprite1.setPosition(posPlayer - spriteCenter);
    mSprite2.setPosition(posPlayer - spriteCenter - sf::Vector2f(mSprite1.getGlobalBounds().width, 0));
}

void ParallaxLayer::SetPositionY(float posY)
{
    mSprite1.setPosition(sf::Vector2f(mSprite1.getPosition().x, posY - 50));
    mSprite2.setPosition(sf::Vector2f(mSprite2.getPosition().x, posY - 50));
}

void ParallaxLayer::Draw(sf::RenderWindow& window)
{
    window.draw(mSprite1);
    window.draw(mSprite2);
}