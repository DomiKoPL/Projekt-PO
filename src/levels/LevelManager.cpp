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

        std::map<std::pair<float, float>, std::vector<sf::Vector2f>> best_formation_pos;

        {
            std::vector<std::pair<sf::Vector2f, int>> temp;
            uint cnt = 0;
            
            for(auto& [enemy_number, enemy] : args["enemies"].items()) {
                auto X = enemy.at("X").get<std::vector<float>>();
                auto Y = enemy.at("Y").get<std::vector<float>>();
                auto count = enemy.at("count").get<uint>();
                cnt += count;
                auto x = X.back(), y = Y.back();
                temp.push_back({{x, y}, count});
            }
            decltype(formation_temp) form;

            uint roz_size = 8;
            while(form.size() < cnt) {
                uint roz = form.size() + roz_size;
                roz_size = 15 - roz_size;
                roz = std::min((uint)formation_temp.size(), roz);
                form = std::vector<sf::Vector2f>(formation_temp.begin(), formation_temp.begin() + roz);
            }
            
            while(cnt--) {
                float dbest = 1e9;
                for(auto& [p, c] : temp) {
                    if(not c) continue;
                    for(auto& p2 : form) {
                        auto d = (p.x - p2.x) * (p.x - p2.x) + (p.y - p2.y) * (p.y - p2.y);
                        dbest = std::min(dbest, d);
                    }
                }
                bool g = 0;
                for(auto& [p, c] : temp) {
                    if(not c) continue;
                    for(auto& p2 : form) {
                        auto d = (p.x - p2.x) * (p.x - p2.x) + (p.y - p2.y) * (p.y - p2.y);
                        if(abs(d - dbest) <= 0.1f) {
                            g = 1;
                            Log::log(Log::INFO, "best = {} {}, {} {}\n", p.x, p.y, p2.x, p2.y);
                            best_formation_pos[{p.x, p.y}].push_back(p2);
                            form.erase(std::find(form.begin(), form.end(), p2));
                            c--;
                            break;
                        }
                    }
                    if(g) break;
                }

                if(not g) {
                    Log::log(Log::INFO, "GOWNO {}\n", dbest);
                }
            }
        }

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
                    Log::log(Log::INFO, "en = {} {}\n", last_pos.x, last_pos.y);
                    goals.push_back(best_formation_pos[{last_pos.x, last_pos.y}][0]);
                    best_formation_pos[{last_pos.x, last_pos.y}].erase(best_formation_pos[{last_pos.x, last_pos.y}].begin());
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