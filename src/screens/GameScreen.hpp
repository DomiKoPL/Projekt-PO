#pragma once
#include <SFML/Graphics.hpp>
#include "BaseScreen.hpp"

class GameScreen : public BaseScreen {
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float time_diff);
    void handle_event(sf::RenderWindow& window, sf::Event event);
};