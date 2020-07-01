#include "MovingBackground.hpp"

MovingBackground& MovingBackground::instance() {
    static MovingBackground movingBackground;
    return movingBackground;
}

void MovingBackground::draw(sf::RenderWindow& window) const {
    window.draw(m_background_sprite);
}

void MovingBackground::update(float elapsed) {
    if(m_background_mode == 0) {
        m_background_current_y -= m_background_move_speed * elapsed;
        auto[w, h] = m_background_texture.getSize();
        m_background_sprite.setTextureRect(sf::IntRect(0, (int)m_background_current_y, w, h));
    }  else if(m_background_mode == 1) {
        m_background_boost_time_current += elapsed;
        m_background_move_speed += elapsed *  (m_background_max_speed - m_background_min_speed) / (m_background_boost_time / 4.f);
        if(m_background_boost_time_current >= m_background_boost_time / 4.f) {
            m_background_move_speed = m_background_max_speed;
            m_background_mode = 2;
        }
        m_background_current_y -= m_background_move_speed * elapsed;
        auto[w, h] = m_background_texture.getSize();
        m_background_sprite.setTextureRect(sf::IntRect(0, (int)m_background_current_y, w, h));
    } else if(m_background_mode == 2) {
        m_background_boost_time_current += elapsed;
        if(m_background_boost_time_current >= m_background_boost_time * 3.f / 4.f) {
            m_background_mode = 3;
        }
        m_background_current_y -= m_background_move_speed * elapsed;
        auto[w, h] = m_background_texture.getSize();
        m_background_sprite.setTextureRect(sf::IntRect(0, (int)m_background_current_y, w, h));
    } else if(m_background_mode == 3) {
        m_background_boost_time_current += elapsed;
        m_background_move_speed -= elapsed * (m_background_max_speed - m_background_min_speed) / (m_background_boost_time / 4.f);
        if(m_background_boost_time_current >= m_background_boost_time) {
            m_background_move_speed = m_background_min_speed;
            m_background_mode = 4;
        }
        m_background_current_y -= m_background_move_speed * elapsed;
        auto[w, h] = m_background_texture.getSize();
        m_background_sprite.setTextureRect(sf::IntRect(0, (int)m_background_current_y, w, h));
    }
}

int MovingBackground::get_mode() {
    return m_background_mode;
}

void MovingBackground::change_mode(int mode) {
    m_background_mode = mode;
    if(mode == 1) {
        m_background_boost_time_current = 0.f;
    }
}

MovingBackground::MovingBackground() {
    m_background_current_y = 0.f;
    m_background_texture.loadFromFile("Resources/Background/2.png");
    m_background_texture.setRepeated(true);
    
    m_background_sprite.setTexture(m_background_texture);

    auto[tmpx, tmpy] = m_background_texture.getSize();
    m_background_sprite.setScale(1920.f / tmpx, 1080.f / tmpy);
}