#pragma once

#include "../Player.hpp"
#include "../enemies/SmallEnemy.hpp"
#include "../gui/TextGenerator.hpp"
#include <memory>
#include <vector>
#include "../PowerUp.hpp"

class Level
{
private:
    sf::Texture m_level_texture;
    sf::Sprite m_level_sprite;
    std::string n_name;
    std::vector<std::shared_ptr<BaseEnemy>> m_enemies;
    float m_current_time;
    int m_score;
    std::shared_ptr<std::vector<PowerUp>> m_powerups;
    std::shared_ptr<std::vector<std::unique_ptr<Shot>>> m_shots;
    int dir = 1;
    float cnt_time = 1.0f;
    sf::Texture m_score_texture;
    sf::Sprite m_score_sprite;
    sf::Texture m_highscore_texture;
    sf::Sprite m_highscore_sprite;
    
    bool m_demo;
    void random_powerup(Player& player, std::shared_ptr<BaseEnemy>& enemy);
public:
    void draw(sf::RenderWindow &window);
    void update(Player &player, float elapsed);
    void update_demo(float elapsed);
    bool is_end();
    Level(const std::string name, std::vector<std::shared_ptr<BaseEnemy>> enemies, std::shared_ptr<std::vector<PowerUp>> powerups, std::shared_ptr<std::vector<std::unique_ptr<Shot>>> shots, bool demo);
};