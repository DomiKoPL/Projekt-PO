#include "SmallEnemy.hpp"
#include <random>
#include "../Log.hpp"
#include "../MusicManager.hpp"

std::mt19937 gen2{std::random_device{}()};
template <typename T>
T random(T min, T max) {
    using dist = std::conditional_t<std::is_integral<T>::value, 
                    std::uniform_int_distribution<T>, 
                    std::uniform_real_distribution<T>>;
    return dist{min, max}(gen2);
}
	

std::vector<std::unique_ptr<Shot>> SmallEnemy::shot(Player& player, float elapsed) {
    std::vector<std::unique_ptr<Shot>> shots;
    m_time_to_shot -= elapsed;
    if(m_time_to_shot <= 0.f) {
        MusicManager::instance().play_sound("Resources/Space Shooter - 1/Sound/3.wav");
        m_time_to_shot = random(0.1f, 25.f);
        shots.emplace_back(new Shot(180, random(200, 500), 1, 1, "Resources/Space Shooter - 1/Item/Bomb.png", m_sprite.getPosition(), 20));
    }
    return shots;
}


SmallEnemy::SmallEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, float start_rotation, uint hp, const std::string texture_path)
    : BaseEnemy(goals, time_offset, speed, start_rotation, hp, texture_path),
        m_time_to_shot{time_offset + random(4.f, 15.f)}
    {
    
}