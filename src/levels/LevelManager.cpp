#include "LevelManager.hpp"
#include "../Settings.hpp"
#include "../Log.hpp"

void LevelManager::next_level() {
    m_current_level_number++;
    if(not m_levels.count(m_current_level_number)) {
        Log::log(Log::INFO, "Loading {}\n", m_current_level_number);
        m_levels_played += m_current_level_number - 1;
        load();
        return;
    }
    
    Log::log(Log::INFO, "NEXT LEVEL {}\n", m_current_level_number);
    m_current_level = m_levels[m_current_level_number];
}

void LevelManager::draw(sf::RenderWindow& window) {
    m_current_level->draw(window);
}

void LevelManager::update(Player& player, float elapsed) {
    if(m_current_level->is_end()) {
        next_level();
    }
    m_current_level->update(player, elapsed);
}

void LevelManager::load() {
    auto levels = Settings::get<nlohmann::json>("levels");
    for(auto& [level_name, args] : levels.items()) {
        Log::log(Log::INFO, "name = {}\n", level_name);
        auto enemy_hp = args.at("enemy_hp").get<uint>();
        auto texture_path = args.at("enemy_texture_path").get<std::string>();

        std::vector<std::shared_ptr<BaseEnemy>> enemies;

        for(auto& [enemy_number, enemy] : args["enemies"].items()) {
            Log::log(Log::INFO, "enemy = {}\n", enemy_number);
            
            auto speed = enemy.at("speed").get<float>();
            auto time_offset_start = enemy.at("time_offset_start").get<float>();
            auto time_offset = enemy.at("time_offset").get<float>();
            auto type = enemy.at("type").get<std::string>();
            auto x = enemy.at("X").get<std::vector<float>>();
            auto y = enemy.at("Y").get<std::vector<float>>();
            auto count = enemy.at("count").get<uint>();

            std::vector<sf::Vector2f> goals(x.size());
            for(uint i = 0; i < x.size(); i++) {
                goals[i] = {x[i], y[i]};
            }

            if(type == "small") {
                for(uint i = 0; i < count; i++) {
                    enemies.emplace_back(new SmallEnemy(goals, time_offset_start + time_offset * i, speed, enemy_hp, texture_path));
                }
            }
        }

        Log::log(Log::INFO, "Making level, {}\n", level_name);
        uint lvl = std::stoi(level_name) + m_levels_played;
        m_levels[std::stoi(level_name)] = std::make_shared<Level>(std::to_string(lvl), enemies);
    }

    m_current_level = m_levels[1];
    m_current_level_number = 1;
}

LevelManager::LevelManager()
    : m_levels_played{0} {

}

LevelManager::~LevelManager() {

}