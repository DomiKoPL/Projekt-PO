#pragma once
#include "Level.hpp"

class LevelManager {
private:

public:
    void draw(sf::RenderWindow& window);
    void update(Player& player, float elapsed);
    void load();
    LevelManager();
};