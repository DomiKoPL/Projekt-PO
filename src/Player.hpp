#pragma once
#include <SFML/Graphics.hpp>
#include "Spaceship.hpp"
#include "Weapon.hpp"
#include <memory>
#include "effects/Animation.hpp"

class Player : public Spaceship {
private:
    Weapon* m_weapon;
    int m_weapon_numer;
    std::vector<std::unique_ptr<Shot>> m_shots;
    float m_move_speed;
    float m_shoot_frequency;
    float m_time_from_last_shot;
    float m_shield_time;
    int m_life;
    sf::Sprite m_shield;
    int m_score;

    sf::Sprite m_death;
    Animation m_death_animation;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void move_left(float elapsed);
    void move_right(float elapsed);
    void update(float elapsed);

    void shoot();
    std::vector<std::unique_ptr<Shot>>& get_shots();
    void hit();
    
    bool is_dead() const;
    
    void add_score(int score);
    int get_score() const;

    void add_life();
    int get_life() const;

    void add_speed(float speed);
    float get_move_speed() const;

    void add_shoot_speed(float offset);
    float get_shoot_frequency() const;
    
    void upgrade_weapon();
    void downgrade_weapon();
    int get_weapon_number() const;

    void give_shield(float shield_time);
    
    Player();
};