#include "FPSCounter.h"
#include "GameManager.h"
#include <iostream>
#include "PlatFormerScene.h"

FPSCounter::FPSCounter() : frameCount(0), fps(0), lastTime(0) {}

bool FPSCounter::loadFont(const std::string& fontPath) {
    /*if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur : Impossible de charger la police " << fontPath << std::endl;
        return false;
    }*/

    font = GameManager::Get()->GetFont();

    fpsText.setCharacterSize(20.f);
    fpsText.setFont(*font);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);

    return true;
}

void FPSCounter::update(sf::Vector2f pos) {
    frameCount++;
    float currentTime = clock.getElapsedTime().asSeconds();

    std::cout << pos.x << " " << pos.y << std::endl;
    fpsText.setPosition(pos);

    if (currentTime - lastTime >= 1.0f) { // Mise   jour chaque seconde
        fps = frameCount / (currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    }
}

void FPSCounter::draw(sf::RenderWindow& window) {
    window.draw(fpsText);
}
