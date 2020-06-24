#pragma once

#include "../Spaceship.hpp"
#include "../Player.hpp"

class BaseEnemy : public Spaceship {
private:
    std::vector<sf::Vector2f> m_goals;
    uint m_current_goal;
    float m_current_time;
    float m_time_offset;
    float m_speed;
    uint m_hp;
    float m_rotation;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void update(Player& player, float elapsed);
    bool is_visible() const;
    bool is_dead() const;
    void deal_dmg(uint dmg);
    BaseEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, uint hp, const std::string texture_path);
};