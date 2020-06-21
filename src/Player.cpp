#include "Player.hpp"

void Player::move_left(float elapsed) {
    move(-m_move_speed * elapsed, 0);
}

void Player::move_right(float elapsed) {
    move(m_move_speed * elapsed, 0);
}
