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
    m_times_played++;

    auto formation_json = Settings::get<nlohmann::json>("levels_formation");
    auto X = formation_json.at("X").get<std::vector<float>>();
    auto Y = formation_json.at("Y").get<std::vector<float>>();
    std::vector<sf::Vector2f> formation_temp(X.size());
    for(uint i = 0; i < X.size(); i++) {
        formation_temp[i] = {X[i], Y[i]};
    }
    

    auto levels = Settings::get<nlohmann::json>("levels");
    for(auto& [level_name, args] : levels.items()) {
        Log::log(Log::INFO, "name = {}\n", level_name);
        auto formation = formation_temp;
        auto enemy_hp = args.at("enemy_hp").get<uint>();
        auto texture_path = args.at("enemy_texture_path").get<std::string>();

        std::vector<std::shared_ptr<BaseEnemy>> enemies;
        uint enemy_id = 0;

        for(auto& [enemy_number, enemy] : args["enemies"].items()) {
            Log::log(Log::INFO, "enemy = {}\n", enemy_number);
            
            auto speed = enemy.at("speed").get<float>();
            auto time_offset_start = enemy.at("time_offset_start").get<float>();
            auto time_offset = enemy.at("time_offset").get<float>();
            auto type = enemy.at("type").get<std::string>();
            auto x = enemy.at("X").get<std::vector<float>>();
            auto y = enemy.at("Y").get<std::vector<float>>();
            auto count = enemy.at("count").get<uint>();
            auto start_rotation = enemy.at("start_rotation").get<uint>();

            std::vector<sf::Vector2f> goals(x.size());
            for(uint i = 0; i < x.size(); i++) {
                goals[i] = {x[i], y[i]};
            }

            if(type == "small") {
                for(uint i = 0; i < count; i++) {
                    auto last_pos = goals.back();
                    auto it = std::min_element(formation.begin(), formation.end(), [last_pos](auto p1, auto p2) {
                        auto d = [last_pos](auto p) {
                            return (p.x - last_pos.x) * (p.x - last_pos.x) + (p.y - last_pos.y) * (p.y - last_pos.y);
                        };
                        return d(p1) < d(p2);
                    });
                    goals.push_back(*it);
                    formation.erase(it);
                    enemy_id++;
                    enemies.emplace_back(new SmallEnemy(goals, time_offset_start + time_offset * i, speed, start_rotation, m_times_played * enemy_hp, texture_path));
                    goals.pop_back();
                }
            }
        }

        Log::log(Log::INFO, "Making level, {}\n", level_name);
        uint lvl = std::stoi(level_name) + m_levels_played;
        m_levels[std::stoi(level_name)] = std::make_shared<Level>(std::to_string(lvl), enemies);
    }

    m_current_level = m_levels[Settings::get<int>("start_level")];
    m_current_level_number = Settings::get<int>("start_level");
}

LevelManager::LevelManager()
    : m_levels_played{0}, m_times_played{0} {

}

LevelManager::~LevelManager() {

}