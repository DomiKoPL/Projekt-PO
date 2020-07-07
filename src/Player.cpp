#include "Player.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"
#include "MusicManager.hpp"
#include "Settings.hpp"

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

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
    //     m_weapon = Weapons::get_weapon("0");
    //     m_weapon_numer = 0;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
    //     m_weapon = Weapons::get_weapon("1");
    //     m_weapon_numer = 1;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
    //     m_weapon = Weapons::get_weapon("2");
    //     m_weapon_numer = 2;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
    //     m_weapon = Weapons::get_weapon("3");
    //     m_weapon_numer = 3;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
    //     m_weapon = Weapons::get_weapon("4");
    //     m_weapon_numer = 4;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
    //     m_weapon = Weapons::get_weapon("5");
    //     m_weapon_numer = 5;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
    //     m_weapon = Weapons::get_weapon("6");
    //     m_weapon_numer = 6;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
    //     m_weapon = Weapons::get_weapon("7");
    //     m_weapon_numer = 7;
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
    //     m_weapon = Weapons::get_weapon("8");
    //     m_weapon_numer = 8;
    // }
}

void Player::hit() {
    if(m_shield_time <= 0) {
        Log::log(Log::INFO, "PLAYER HIT\n");
        m_life--;
        if(is_dead()) {
            MusicManager::instance().play_sound(Settings::get<std::string>("player", "death_sound"));
        }
        downgrade_weapon();
        give_shield(Settings::get<float>("player", "shield_time_after_hit"));
    }
}

void Player::add_life() {
    if(m_life == Settings::get<int>("player", "life", "max")) {
        add_score(10);
    } else {
        m_life++;
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

int Player::get_weapon_number() const {
    return m_weapon_numer;
}

float Player::get_move_speed() const {
    return m_move_speed;
}

float Player::get_shoot_frequency() const {
    return m_shoot_frequency;
}

void Player::add_speed(float speed) {
    m_move_speed += speed;
    m_move_speed = std::max(m_move_speed, Settings::get<float>("player", "move_speed", "min"));
    m_move_speed = std::min(m_move_speed, Settings::get<float>("player", "move_speed", "max"));
}

void Player::add_shoot_speed(float offset) {
    m_shoot_frequency += offset;
    m_shoot_frequency = std::max(m_shoot_frequency, Settings::get<float>("player", "shoot_frequency", "min"));
    m_shoot_frequency = std::min(m_shoot_frequency, Settings::get<float>("player", "shoot_frequency", "max"));
}

void Player::upgrade_weapon() {
    if(Weapons::count_weapon(std::to_string(m_weapon_numer + 1))) {
        m_weapon_numer++;
        m_weapon = Weapons::get_weapon(std::to_string(m_weapon_numer));
    }
}

void Player::downgrade_weapon() {
    if(Weapons::count_weapon(std::to_string(m_weapon_numer - 1))) {
        m_weapon_numer--;
        m_weapon = Weapons::get_weapon(std::to_string(m_weapon_numer));
    }
}

Player::Player() {
    m_move_speed = Settings::get<float>("player", "move_speed", "initial");
    m_shoot_frequency = Settings::get<float>("player", "shoot_frequency", "initial");
    m_time_from_last_shot = 100.f; // some big value
    m_weapon_numer = Settings::get<int>("player", "weapon");
    m_weapon = Weapons::get_weapon(std::to_string(m_weapon_numer));
    m_shield_time = 0;
    m_life = Settings::get<int>("player", "life", "initial");
    m_score = 0;

    // shield setup
    m_shield.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Shield.png"));
    auto c = m_shield.getColor();
    c.a = 150;
    m_shield.setColor(c);
    auto box = TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Shield.png").getSize();
    m_shield.setOrigin(box.x / 2, box.y / 2);
    m_shield.setScale(1.6, 1.6);

    // death animation setup
    m_death.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/Fx/Fx7.png"));
    int w = 656 / 8;
    m_death.setTextureRect(sf::IntRect(0, 0, w, 72));
    m_death.setOrigin(w / 2.f, 72.f / 2);
    // 656 / 8, 72
    for(int i = 0; i < 8; i++) {
        m_death_animation.addFrame({sf::IntRect(i * w, 0, w, 72), 0.1});
    }
}