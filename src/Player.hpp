#pragma once
#include <SFML/Graphics.hpp>
#include "Spaceship.hpp"
#include "Weapon.hpp"
#include <memory>

class Player : public Spaceship {
private:
    Weapon* m_weapon;
    std::vector<std::unique_ptr<Shot>> m_shots;
    float m_move_speed = 150.f;
    float m_shoot_frequency = 0.5f;
    float m_time_from_last_shot;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void move_left(float elapsed);
    void move_right(float elapsed);
    void shoot();
    void update(float elapsed);
    
    Player();
};