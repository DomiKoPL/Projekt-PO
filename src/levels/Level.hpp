#pragma once

#include "../Player.hpp"
#include "../enemies/SmallEnemy.hpp"
#include "../gui/TextGenerator.hpp"
#include <memory>

class Level
{
private:
    sf::Texture m_level_texture;
    sf::Sprite m_level_sprite;
    std::string n_name;
    std::vector<std::shared_ptr<BaseEnemy>> m_enemies;
    float m_current_time;

    int dir = 1;
    float cnt_time = 1.5f;

public:
    void draw(sf::RenderWindow &window);
    void update(Player &player, float elapsed);
    bool is_end();
    Level(const std::string name, std::vector<std::shared_ptr<BaseEnemy>> enemies);
};