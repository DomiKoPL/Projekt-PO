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
    void next_level();
public:
    void draw(sf::RenderWindow& window);
    void update(Player& player, float elapsed);
    void load();
    LevelManager();
    ~LevelManager();
};