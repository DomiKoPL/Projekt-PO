#include "Player.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"
#include "MusicManager.hpp"

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
    if(is_dead()) {
        if(not m_death_animation.is_done()) {
            Spaceship::draw(target, states);
            target.draw(m_death);
        }

        return;
    }

    for (auto& shot : m_shots) {
        target.draw(*shot, states);
    }
    Spaceship::draw(target, states);
    // Log::log(Log::INFO, "Shield = {}\n", m_shield_time);
    if(m_shield_time > 0) {
        target.draw(m_shield, states);
    }
}

void Player::update(float elapsed) {
    if(is_dead()) {
        m_death.setPosition(m_sprite.getPosition());
        m_death_animation.update(m_death, elapsed);
        return;
    }
    m_time_from_last_shot += elapsed;
    m_shield_time -= std::min(m_shield_time, elapsed);

    if(m_shield_time > 0) {
        auto c = m_shield.getColor();
        c.a = std::min(1.5f, m_shield_time) * (100 / 1.5f) + 60;
        m_shield.setColor(c);
    }

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
        if(is_dead()) {
            MusicManager::instance().play_sound("Resources/Space Shooter - 1/Sound/Death.wav");
        }
        give_shield(1.5);
    }
}

int Player::get_life() const {
    return m_life;
}

void Player::add_score(int score) {
    m_score += score;
}

int Player::get_score() const {
    return m_score;
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
    m_shield_time = 5;
    m_life = 3;
    m_score = 0;
    m_shield.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Shield.png"));
    auto c = m_shield.getColor();
    c.a = 150;
    m_shield.setColor(c);
    auto box = TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Shield.png").getSize();
    Log::log(Log::INFO, "BOXX = {} {}\n", box.x, box.y);
    m_shield.setOrigin(box.x / 2, box.y / 2);
    m_shield.setScale(1.6, 1.6);

    m_death.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Fx7.png"));
    int w = 656 / 8;
    m_death.setTextureRect(sf::IntRect(0, 0, w, 72));
    m_death.setOrigin(w / 2.f, 72.f / 2);
    // 656 / 8, 72
    for(int i = 0; i < 8; i++) {
        m_death_animation.addFrame({sf::IntRect(i * w, 0, w, 72), 0.1});
    }
}