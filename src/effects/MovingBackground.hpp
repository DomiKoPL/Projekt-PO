#pragma once
#include <SFML/Graphics.hpp>

class MovingBackground {
private:
    sf::Texture m_background_texture;
    sf::Sprite m_background_sprite;

    int m_background_mode = 0;
    float m_background_move_speed = 10.f;
    float m_background_min_speed = 10.f;
    float m_background_max_speed = 2000.f;
    float m_background_current_y = 0.f;
    float m_background_boost_time_current;
    float m_background_boost_time = 6.f;
public:
    static MovingBackground& instance();
    void draw(sf::RenderWindow& window) const;
    void update(float elapsed);
    int get_mode();
    void change_mode(int mode);
    MovingBackground();
};