#pragma once
#include "BaseEnemy.hpp"

class SmallEnemy : public BaseEnemy {

public:
    SmallEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, float start_rotation, uint hp, const std::string texture_path);
};