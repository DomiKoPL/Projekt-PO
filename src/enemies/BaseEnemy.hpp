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
    bool m_path_end;

    float m_random_goal_x;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void update(Player& player, float elapsed);
    bool is_visible() const;
    bool is_dead() const;
    bool path_end();
    void deal_dmg(uint dmg);
    void move_right(float elapsed);
    void move_left(float elapsed);
    void move_random_down(float elapsed);
    BaseEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, uint hp, const std::string texture_path);
};