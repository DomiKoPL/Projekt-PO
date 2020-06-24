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
        auto shots = m_weapon->shoot(m_sprite.getPosition());
        for (auto& shot : shots) {
            m_shots.push_back(std::move(shot));
        }
    }
}

std::vector<std::unique_ptr<Shot>>& Player::get_shots() {
    return m_shots;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& shot : m_shots) {
        target.draw(*shot, states);
    }
    Spaceship::draw(target, states);
}

void Player::update(float elapsed) {
    m_time_from_last_shot += elapsed;
    for(auto& shot : m_shots) {
        shot->update(elapsed);
    }


    m_shots.erase(std::remove_if(m_shots.begin(), m_shots.end(), [](std::unique_ptr<Shot>& shot) {
        return shot->is_dead();
    }), m_shots.end());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        m_weapon = Weapons::get_weapon("0");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        m_weapon = Weapons::get_weapon("1");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        m_weapon = Weapons::get_weapon("2");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        m_weapon = Weapons::get_weapon("3");
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        m_weapon = Weapons::get_weapon("8");
    }
}

void Player::hit() {
    Log::log(Log::INFO, "PLAYER HIT\n");
}

bool Player::is_dead() const {
    return false;
}

Player::Player() {
    m_move_speed = 2000.f;
    m_shoot_frequency = 0.5f;
    m_time_from_last_shot = 100.f;
    m_weapon = Weapons::get_weapon("0");
}