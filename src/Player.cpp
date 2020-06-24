#include "Player.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

void Player::move_left(float elapsed) {
    float x = m_sprite.getPosition().x - m_sprite.getGlobalBounds().width / 2;
    float max_dx = 0.f - x; //! CHANGE FOR LEFT BORDER
    float dx = -m_move_speed * elapsed;
    dx = std::max(dx, max_dx);
    move(dx, 0);
    m_shield.setPosition(m_sprite.getPosition());
}

void Player::move_right(float elapsed) {
    float x = m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2;
    float max_dx = 1920.f - x; //! CHANGE FOR RIGHT BORDER
    float dx = m_move_speed * elapsed;
    dx = std::min(dx, max_dx);
    move(dx, 0);
    m_shield.setPosition(m_sprite.getPosition());
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
    Log::log(Log::INFO, "Shield = {}\n", m_shield_time);
    if(m_shield_time > 0) {
        target.draw(m_shield, states);
    }
}

void Player::update(float elapsed) {
    m_time_from_last_shot += elapsed;
    m_shield_time -= std::min(m_shield_time, elapsed);

    m_shield.setPosition(m_sprite.getPosition());

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
    if(m_shield_time <= 0) {
        Log::log(Log::INFO, "PLAYER HIT\n");
        m_life--;
        give_shield(1.5);
    }
}

void Player::give_shield(float shield_time) {
    m_shield_time += shield_time;
}

bool Player::is_dead() const {
    return m_life <= 0;
}

Player::Player() {
    m_move_speed = 2000.f;
    m_shoot_frequency = 0.5f;
    m_time_from_last_shot = 100.f;
    m_weapon = Weapons::get_weapon("0");
    m_shield_time = 0;
    m_life = 3;
    m_shield.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Shield.png"));
    auto c = m_shield.getColor();
    c.a = 150;
    m_shield.setColor(c);
    auto box = TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Shield.png").getSize();
    Log::log(Log::INFO, "BOXX = {} {}\n", box.x, box.y);
    m_shield.setOrigin(box.x / 2, box.y / 2);
    m_shield.setScale(1.6, 1.6);
}