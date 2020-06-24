#pragma once
#include "BaseEnemy.hpp"

class SmallEnemy : public BaseEnemy {

public:
    SmallEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, uint hp, const std::string texture_path);
};