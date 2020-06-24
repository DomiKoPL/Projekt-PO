#pragma once
#include "BaseEnemy.hpp"

class SmallEnemy : public BaseEnemy {
private:
    float m_time_to_shot;
public:
    virtual std::vector<std::unique_ptr<Shot>> shot(Player& player, float elapsed);
    SmallEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, float start_rotation, uint hp, const std::string texture_path);
};