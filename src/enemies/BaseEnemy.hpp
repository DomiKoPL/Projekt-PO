#pragma once

#include "../Spaceship.hpp"
#include "../Player.hpp"
#include "../Shot.hpp"
#include "../effects/Animation.hpp"

class BaseEnemy : public Spaceship {
protected:
    std::vector<sf::Vector2f> m_goals;
    uint m_current_goal;
    float m_current_time;
    float m_time_offset;
    float m_speed;
    uint m_hp;
    float m_rotation;
    bool m_path_end;
    float m_random_goal_x;
    
    sf::Sprite m_death;
    Animation m_death_animation;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    virtual std::vector<std::unique_ptr<Shot>> shot(Player& player, float elapsed) = 0;
    void update(Player& player, float elapsed);
    bool is_visible() const;
    bool is_dead() const;
    bool path_end();
    void deal_dmg(uint dmg);
    void move_right(float elapsed);
    void move_left(float elapsed);
    void move_random_down(float elapsed);
    sf::Vector2f get_position() const;
    BaseEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, float start_rotation, uint hp, const std::string texture_path);
};