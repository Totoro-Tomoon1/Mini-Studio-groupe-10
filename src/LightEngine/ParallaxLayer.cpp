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
    mSprite2.setPosition(mSprite1.getGlobalBounds().width, 0);

    mSpeed = speed;
}

void ParallaxLayer::Update(Player* player)
{
    // Récupération du déplacement du joueur
    sf::Vector2f offset = *player->GetDepl();
    sf::Vector2f playerPos = player->GetPosition();

    // Calcul de la position cible du fond (avec un ajustement horizontal en fonction du joueur)
    float newX = playerPos.x - player->GetScene()->GetWindowWidth() / 2;

    // Déplacement des sprites de fond en fonction du mouvement du joueur
    // Ici, nous gardons un défilement continu et un parallaxe modéré (mSpeed ajusté)
    //mSprite1.move(offset.x * mSpeed, 0);  // Déplacement horizontal du fond en fonction du joueur
    //mSprite2.move(offset.x * mSpeed, 0);  // Déplacement horizontal du fond en fonction du joueur

    mSprite1.setPosition(mSprite1.getPosition().x - offset.x * mSpeed + offset.x, mSprite1.getPosition().y);
    mSprite2.setPosition(mSprite2.getPosition().x - offset.x * mSpeed + offset.x, mSprite2.getPosition().y);

    // Calcul de la largeur des sprites pour la gestion de la répétition du fond
    float spriteWidth = mSprite1.getGlobalBounds().width;

    // Réinitialisation du sprite 1 (quand il sort de l'écran à gauche)
    if (mSprite1.getPosition().x <= newX - spriteWidth)
    {
        mSprite1.setPosition(mSprite2.getPosition().x + spriteWidth, mSprite1.getPosition().y);
    }
    // Réinitialisation du sprite 1 (quand il sort de l'écran à droite)
    else if (mSprite1.getPosition().x >= newX + spriteWidth)
    {
        mSprite1.setPosition(mSprite2.getPosition().x - spriteWidth, mSprite1.getPosition().y);
    }

    // Réinitialisation du sprite 2 (quand il sort de l'écran à gauche)
    if (mSprite2.getPosition().x <= newX - spriteWidth)
    {
        mSprite2.setPosition(mSprite1.getPosition().x + spriteWidth, mSprite2.getPosition().y);
    }
    // Réinitialisation du sprite 2 (quand il sort de l'écran à droite)
    else if (mSprite2.getPosition().x >= newX + spriteWidth)
    {
        mSprite2.setPosition(mSprite1.getPosition().x - spriteWidth, mSprite2.getPosition().y);
    }

    // Ajustement de la position horizontale des sprites en fonction de la position du joueur
   /* mSprite1.setPosition(newX, mSprite1.getPosition().y);
    mSprite2.setPosition(newX + spriteWidth, mSprite2.getPosition().y);*/

}


void ParallaxLayer::SetPosition(sf::Vector2f posPlayer)
{
    // On calcule le centre du sprite en utilisant son origine (par défaut, l'origine est en haut à gauche)
    sf::FloatRect bounds = mSprite1.getGlobalBounds();
    sf::Vector2f spriteCenter(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

    // On ajuste la position en fonction de posPlayer pour centrer le sprite
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
    //std::cout << "mSprite1 : " << mSprite1.getPosition().x << "      " << mSprite1.getPosition().y << std::endl;
    //std::cout << "mSprite2 : " << mSprite2.getPosition().x << "      " << mSprite2.getPosition().y << std::endl;

    window.draw(mSprite1);
    window.draw(mSprite2);
}
