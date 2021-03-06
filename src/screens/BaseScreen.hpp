#pragma once
#include <SFML/Graphics.hpp>

class BaseScreen {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(sf::RenderWindow& window, float elapsed) = 0;
    virtual void handle_event(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void reset() = 0;
    virtual ~BaseScreen() = default;
};