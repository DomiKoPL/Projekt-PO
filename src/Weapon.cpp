#include "Weapon.hpp"
#include "Settings.hpp"
#include "Log.hpp"

bool Weapon::can_shoot(float time_from_last_shot, float shoot_frequency) {
    shoot_frequency *= m_shoot_frequency_multiplier;
    return time_from_last_shot >= shoot_frequency;
}

std::vector<Shot*> Weapon::shoot() {
    Log::log(Log::INFO, "{}\n", m_name);
    return {};
}

Weapon::Weapon(float shoot_frequency_multiplier, float shoot_speed, std::vector<float> shoot_angles, std::vector<float> shoot_offset, std::string texture_path, std::string name, sf::Vector2f size) {
    m_shoot_frequency_multiplier = shoot_frequency_multiplier;
    m_shoot_speed = shoot_speed;
    m_shoot_angles = shoot_angles;
    m_shoot_offset = shoot_offset;
    m_texture_path = texture_path;
    m_name = name;
    m_size = size;
}

Weapon* Weapons::get_weapon(const std::string name) {
    if(not m_weapons.count(name)) {
        Log::log(Log::ERROR, "Weapon \"{}\" not found!\n", name);
    }
    return m_weapons[name];
}

#include <iostream>
void Weapons::load() {
    auto weapons = Settings::get<nlohmann::json>("weapons");
    for(auto& [name, args] : weapons.items()) {
        std::cout << name << "\n";
        m_weapons[name] = new Weapon((float)args["shoot_frequency_multiplier"], (float)args["shoot_speed"], args.at("angles").get<std::vector<float>>(), args.at("offset").get<std::vector<float>>(), (std::string)args["texture_path"], (std::string)args["name"], sf::Vector2f(args["size"][0], args["size"][1]));
    }
}