#pragma once
#include <SFML/Graphics.hpp>
#include "Shot.hpp"
#include <vector>
#include <map>
#include <memory>

class Weapon {
private:
    float m_shoot_frequency_multiplier;
    float m_shoot_speed;
    uint m_damage;
    uint m_penetration;
    std::vector<float> m_shoot_angles, m_shoot_offset;
    std::string m_texture_path;
    std::string m_name;
    float m_size;
public:
    bool can_shoot(float time_from_last_shot, float shoot_frequency);
    std::vector<std::unique_ptr<Shot>> shoot(sf::Vector2f position);
    Weapon(float shoot_frequency_multiplier, float shoot_speed, uint damage, uint penetration, std::vector<float> shoot_angles, std::vector<float> shoot_offset, std::string texture_path, std::string name, float size);
};


class Weapons {
private:
    inline static std::map<const std::string, Weapon*> m_weapons;
public:
    static Weapon* get_weapon(const std::string name);
    static void load();
};