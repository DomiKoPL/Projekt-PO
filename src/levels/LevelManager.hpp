#pragma once

#include "Level.hpp"
#include "../Player.hpp"

class LevelManager {

public:
    void draw(sf::RenderWindow& window);
    void update(Player& player, float elapsed);
    void load();
};