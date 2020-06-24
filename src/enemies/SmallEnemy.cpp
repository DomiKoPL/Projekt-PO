#include "SmallEnemy.hpp"



SmallEnemy::SmallEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, float start_rotation, uint hp, const std::string texture_path)
    : BaseEnemy(goals, time_offset, speed, start_rotation, hp, texture_path) {
    
}