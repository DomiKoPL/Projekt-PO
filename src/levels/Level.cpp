#include "Level.hpp"

void Level::draw(sf::RenderWindow& window) {
    if(m_current_time <= 5.5) {
        window.draw(m_level_sprite);
    }

    for(auto& shot : m_shots) {
        window.draw(*shot);
    }
    
    for(auto& enemy : m_enemies) {
        window.draw(*enemy);
    }
}
#include "../Log.hpp"

void Level::update(Player& player, float elapsed) {
    for(auto& shot : m_shots) {
        shot->update(elapsed);
    }
    
    m_current_time += elapsed;

    uint path_ends = 0;
    for(auto& enemy : m_enemies) {
        path_ends += enemy->path_end();
    }

    // Log::log(Log::INFO, "xd = {}\n", path_ends);
    if(path_ends == m_enemies.size()) {
        if(m_enemies.size() <= 5u) {
            for(auto& enemy : m_enemies) {
                enemy->move_random_down(elapsed);
            }
        } else {
            cnt_time -= elapsed;

            if(cnt_time < 0) {
                dir = 1 - dir;
                cnt_time = 2.0f;
            }

            for(auto& enemy : m_enemies) {
                if(dir == 1) {
                    enemy->move_left(elapsed);
                } else {
                    enemy->move_right(elapsed);
                }
            }
        }
    }

    for(auto& enemy : m_enemies) {
        enemy->update(player, elapsed);
        auto shots = enemy->shot(player, elapsed);
        for(auto& shot : shots) {
            m_shots.push_back(std::move(shot));
        }
    }
    
    auto& player_shots = player.get_shots();
    for(auto& enemy : m_enemies) {
        if(enemy->is_visible()) {
            for(auto& shot : player_shots) {
                if(enemy->is_colliding_with(*shot)) {
                    enemy->deal_dmg(shot->get_damage());
                    shot->shot();
                }
            }
            player_shots.erase(std::remove_if(player_shots.begin(), player_shots.end(), [](auto& shot) {
                return shot->is_dead();
            }), player_shots.end());
        }

        if(enemy->is_colliding_with(player)) {
            player.hit();
        }
    }

    for(auto& shot : m_shots) {
        if(shot->is_colliding_with(player)) {
            player.hit();
            shot->shot();
        }
    }

    m_shots.erase(std::remove_if(m_shots.begin(), m_shots.end(), [](auto& shot) {
        return shot->is_dead();
    }), m_shots.end());


    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](auto& enemy) {
        return enemy->is_dead();
    }), m_enemies.end());
}

bool Level::is_end() {
    return m_enemies.size() == 0u;
}

Level::Level(const std::string name, std::vector<std::shared_ptr<BaseEnemy>> enemies) 
    : n_name{name}, 
      m_enemies{enemies},
      m_current_time{0}
    {
    m_level_texture = TextGenerator::get_text_texture("LEVEL " + name, 1.8 * 37 * (6 + name.size()));
    m_level_sprite.setTexture(m_level_texture);
    m_level_sprite.setPosition(1920.f / 2 - m_level_texture.getSize().x / 2, 130);
}