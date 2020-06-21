#include "Player.hpp"
#include "Log.hpp"

void Player::move_left(float elapsed) {
    move(-m_move_speed * elapsed, 0);
}

void Player::move_right(float elapsed) {
    move(m_move_speed * elapsed, 0);
}

void Player::shoot() {
    if(m_weapon->can_shoot(m_time_from_last_shot, m_shoot_frequency)) {
        m_time_from_last_shot = 0.f;
        Log::log(Log::ERROR, "Player shoot!\n");
        m_weapon->shoot();
    }
}

void Player::update(float elapsed) {
    m_time_from_last_shot += elapsed;
}

Player::Player() {
    m_move_speed = 150.f;
    m_shoot_frequency = 0.5f;
    m_time_from_last_shot = 100.f;
    m_weapon = Weapons::get_weapon("1");
}