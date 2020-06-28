#pragma once
#include "Level.hpp"
#include <map>
#include <memory>
#include "../PowerUp.hpp"
#include <vector>

class LevelManager {
private:
    std::map<uint, std::shared_ptr<Level>> m_levels;
    std::shared_ptr<Level> m_current_level;
    uint m_current_level_number, m_levels_played, m_times_played;
    std::shared_ptr<std::vector<PowerUp>> m_powerups;
    std::shared_ptr<std::vector<std::unique_ptr<Shot>>> m_shots;
    bool m_demo;

    sf::Texture m_background_texture;
    sf::Sprite m_background_sprite;

    bool m_pause;

    int m_background_mode = 0;
    float m_background_move_speed = 10.f;
    float m_background_min_speed = 10.f;
    float m_background_max_speed = 2000.f;
    float m_background_current_y = 0.f;
    float m_background_boost_time_current;
    float m_background_boost_time = 6.f;
    
    void next_level();
public:
    void draw(sf::RenderWindow& window);
    void update(Player& player, float elapsed);
    void load();
    void update_demo(float elapsed);
    void flip_pause();
    LevelManager(bool demo);
    LevelManager();
    ~LevelManager();
};