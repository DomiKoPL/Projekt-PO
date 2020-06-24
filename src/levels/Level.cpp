#include "Level.hpp"

void Level::draw(sf::RenderWindow& window) {
    if(m_current_time <= 5.5) {
        window.draw(m_level_sprite);
    }
    
    for(auto& enemy : m_enemies) {
        window.draw(*enemy);
    }
}
#include "../Log.hpp"

void Level::update(Player& player, float elapsed) {
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
                cnt_time = 1.5f;
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
    }
    
    auto& shots = player.get_shots();
    for(auto& enemy : m_enemies) {
        if(enemy->is_visible()) {
            for(auto& shot : shots) {
                if(enemy->is_colliding_with(*shot)) {
                    enemy->deal_dmg(shot->get_damage());
                    shot->shot();
                }
            }
            shots.erase(std::remove_if(shots.begin(), shots.end(), [](auto& shot) {
                return shot->is_dead();
            }), shots.end());
        }
    }

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
    m_level_texture = TextGenerator::get_text_texture("LEVEL " + name, 37 * (6 + name.size()));
    m_level_sprite.setTexture(m_level_texture);
    m_level_sprite.setPosition(1920.f / 2 - m_level_texture.getSize().x / 2, 90);
}