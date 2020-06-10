#pragma once
#include <SFML/Graphics.hpp>
#include "BaseScreen.hpp"
#include "../Spaceship.hpp"
#include "../gui/Button.hpp"

class GameScreen : public BaseScreen {
private:

public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
};