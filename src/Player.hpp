#pragma once
#include <SFML/Graphics.hpp>
#include "Spaceship.hpp"
#include "Weapon.hpp"

class Player : public Spaceship {
private:
    Weapon* m_weapon;
    float m_move_speed = 150.f;
    float m_shoot_frequency = 0.5f;
    float m_time_from_last_shot;
public:
    void move_left(float elapsed);
    void move_right(float elapsed);
    void shoot();
    void update(float elapsed);
    
    Player();
};