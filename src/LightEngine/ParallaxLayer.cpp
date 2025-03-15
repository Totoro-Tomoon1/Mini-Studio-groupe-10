#include "ParallaxLayer.h"
#include <iostream>

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
        std::cerr << "Erreur : l'image copiée depuis la texture est vide !" << std::endl;
        return;
    }

    //ConvertToGrayscale();

    mSprite1.setTexture(*texture);
    mSprite1.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
    mSprite1.setScale(sf::Vector2f(1280.f / 1920.f * 1.1f, 720.f / 1080.f * 1.1f));

    mSprite2.setTexture(*texture);
    mSprite2.setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
    mSprite2.setScale(sf::Vector2f(1280.f / 1920.f * 1.1f, 720.f / 1080.f * 1.1f));
    mSprite2.setPosition(mSprite1.getLocalBounds().width, 0);

    mSpeed = speed;
}

void ParallaxLayer::Update(sf::Vector2f offset)
{
    mSprite1.move(-offset.x * mSpeed, -offset.y * mSpeed);
    mSprite2.move(-offset.x * mSpeed, -offset.y * mSpeed);

    float spriteWidth = mSprite1.getGlobalBounds().width;

    // Réinitialisation du sprite 1 (horizontal)
    if (mSprite1.getPosition().x <= -spriteWidth) {
        mSprite1.setPosition(mSprite2.getPosition().x + spriteWidth, mSprite1.getPosition().y);
    }
    else if (mSprite1.getPosition().x >= spriteWidth) {
        mSprite1.setPosition(mSprite2.getPosition().x - spriteWidth, mSprite1.getPosition().y);
    }

    // Réinitialisation du sprite 2 (horizontal)
    if (mSprite2.getPosition().x <= -spriteWidth) {
        mSprite2.setPosition(mSprite1.getPosition().x + spriteWidth, mSprite2.getPosition().y);
    }
    else if (mSprite2.getPosition().x >= spriteWidth) {
        mSprite2.setPosition(mSprite1.getPosition().x - spriteWidth, mSprite2.getPosition().y);
    }
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
