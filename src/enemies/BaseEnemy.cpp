#include "BaseEnemy.hpp"
#include <math.h>
#include "../Log.hpp"


void BaseEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_current_time < m_time_offset) {
        return;
    }
    Spaceship::draw(target, states);
}

void BaseEnemy::update(Player& player, float elapsed) {
    m_current_time += elapsed;

    if(m_current_time < m_time_offset) {
        // Log::log(Log::INFO, "Not yet {} {}\n", m_current_time, m_time_offset);
        return;
    }

    if(m_current_goal < m_goals.size()) {
        auto[x, y] = m_sprite.getPosition();
        auto[nx, ny] = m_goals[m_current_goal];
        // Log::log(Log::INFO, "Pos = ({}, {}), goal = ({}, {})\n", x, y, nx, ny);
        float dist_to_target = std::sqrt((x - nx) * (x - nx) + (y - ny) * (y - ny));
        
        if(dist_to_target <= 20.f) {
            // Log::log(Log::INFO, "Next goal!\n");
            m_current_goal++;
        } else {
            auto angle = std::atan2(ny - y, nx - x) * 180 / M_PI;
            while(angle < 0) angle += 360.0;
            while(m_rotation < 0) m_rotation += 360.0;
            while(angle >= 360.0) angle -= 360.0;
            while(m_rotation >= 360.0) m_rotation -= 360.0;

            auto angle_change = angle - m_rotation;
            if(angle_change > 180.0) {
                angle_change -= 360.0;
            } else if(angle_change <= -180.0) {
                angle_change += 360.0;
            }
            
            float angle_change_per_second = 45.f;
            if(angle_change > elapsed * angle_change_per_second) angle_change = elapsed * angle_change_per_second;
            if(angle_change < -elapsed * angle_change_per_second) angle_change = -elapsed * angle_change_per_second;
            // Log::log(Log::INFO, "cur = {} ang = {}, change = {}\n", m_rotation, angle, angle_change);
            m_rotation += angle_change;
            set_rotation(m_rotation + 90);
            // Log::log(Log::INFO, "move vector = ({}, {})\n", m_speed * elapsed * std::cos(angle_rad), m_speed * elapsed * std::sin(angle_rad));
            float dangle = m_rotation * M_PI / 180;
            move(m_speed * elapsed * std::cos(dangle),
                    m_speed * elapsed * std::sin(dangle));
        }
    }
}

bool BaseEnemy::is_visible() const {
    if(m_current_time >= m_time_offset) {
        auto box = m_sprite.getGlobalBounds();
        if(box.intersects(sf::FloatRect(0, 0, 1920, 1080))) {
            return true;
        }
    }
    return false;
}

bool BaseEnemy::is_dead() const {
    return m_hp == 0;
}

void BaseEnemy::deal_dmg(uint dmg) {
    m_hp -= std::min(m_hp, dmg);
}

BaseEnemy::BaseEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, uint hp, const std::string texture_path) 
    :   m_goals{goals}, 
        m_current_goal{1}, 
        m_time_offset{time_offset}, 
        m_current_time{0}, 
        m_speed{speed}, 
        m_hp{hp},
        m_rotation{90}
    {
    set_texture(texture_path);
    set_position(goals.at(0));
    set_rotation(0);
}