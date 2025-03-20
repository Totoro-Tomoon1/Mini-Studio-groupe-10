#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class FPSCounter 
{
    sf::Clock clock;
    int frameCount;
    float fps;
    float lastTime;
    sf::Font* font;
    sf::Text fpsText;

public:
    FPSCounter();

    bool loadFont();
    void update(sf::Vector2f pos);
    void draw(sf::RenderWindow& window);
};


