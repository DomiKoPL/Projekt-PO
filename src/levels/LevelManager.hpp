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

    bool m_pause;
    void next_level();
public:
    void draw(sf::RenderWindow& window);
    void update(Player& player, float elapsed);
    void load();
    void update_demo(float elapsed);
    void flip_pause();
    uint get_current_level() const;
    LevelManager(bool demo);
    LevelManager();
    ~LevelManager();
};