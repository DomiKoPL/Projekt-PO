#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
public:
    void run();

    Game();
    ~Game();
};