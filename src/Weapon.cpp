#include "Weapon.hpp"
#include "Settings.hpp"
#include "Log.hpp"

bool Weapon::can_shoot(float time_from_last_shot, float shoot_frequency) {
    shoot_frequency /= m_shoot_frequency_multiplier;
    return time_from_last_shot >= shoot_frequency;
}

std::vector<std::unique_ptr<Shot>> Weapon::shoot(sf::Vector2f position) {
    // Log::log(Log::INFO, "{}\n", m_name);
    std::vector<std::unique_ptr<Shot>> shots;
    for(uint i = 0; i < m_shoot_angles.size(); i++) {
        shots.emplace_back(new Shot(m_shoot_angles[i], m_shoot_speed, m_damage, m_penetration, m_texture_path, position + sf::Vector2f(m_shoot_offset[i], 0.f), m_size));
    }
    return shots;
}

Weapon::Weapon(float shoot_frequency_multiplier, float shoot_speed, uint damage, uint penetration, std::vector<float> shoot_angles, std::vector<float> shoot_offset, std::string texture_path, std::string name, float size) {
    m_shoot_frequency_multiplier = shoot_frequency_multiplier;
    m_shoot_speed = shoot_speed;
    m_damage = damage;
    m_penetration = penetration;
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

void Weapons::load() {
    auto weapons = Settings::get<nlohmann::json>("weapons");
    for(auto& [name, args] : weapons.items()) {
        m_weapons[name] = new Weapon((float)args["shoot_frequency_multiplier"], (float)args["shoot_speed"], args.at("damage").get<uint>(),args.at("penetration").get<uint>(), args.at("angles").get<std::vector<float>>(), args.at("offset").get<std::vector<float>>(), (std::string)args["texture_path"], (std::string)args["name"], float(args["size"]));
    }
}