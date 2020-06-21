#pragma once
#include <SFML/Graphics.hpp>
#include "Spaceship.hpp"

class Player : public Spaceship {
private:
    float m_move_speed = 150.f;
    
public:
    void move_left(float elapsed);
    void move_right(float elapsed);
};