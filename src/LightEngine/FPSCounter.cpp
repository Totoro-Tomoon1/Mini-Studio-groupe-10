#include "FPSCounter.h"

FPSCounter::FPSCounter() : frameCount(0), fps(0), lastTime(0) {}

bool FPSCounter::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur : Impossible de charger la police " << fontPath << std::endl;
        return false;
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);

    return true;
}

void FPSCounter::update() {
    frameCount++;
    float currentTime = clock.getElapsedTime().asSeconds();

    if (currentTime - lastTime >= 1.0f) { // Mise à jour chaque seconde
        fps = frameCount / (currentTime - lastTime);
        frameCount = 0;
        lastTime = currentTime;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    }
}

void FPSCounter::draw(sf::RenderWindow& window) {
    window.draw(fpsText);
}
