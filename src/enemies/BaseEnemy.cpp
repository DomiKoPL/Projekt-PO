#include "BaseEnemy.hpp"
#include <math.h>
#include "../Log.hpp"
#include <random>

void BaseEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_current_time < m_time_offset) {
        return;
    }

    for(auto& [x, y] : m_goals) {
        sf::CircleShape circle;
        circle.setRadius(10);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(x, y);
        target.draw(circle, states);
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
        float good_dist = 20.f;
        if(m_current_goal + 1 == m_goals.size()) {
            good_dist = 0.f; 
        }
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
            float speed_boost = 1.0;
            if(m_current_goal + 1 == m_goals.size()) {
                angle_change_per_second = 1000;
                speed_boost *= 3;
            }

            if(angle_change > elapsed * angle_change_per_second) angle_change = elapsed * angle_change_per_second;
            if(angle_change < -elapsed * angle_change_per_second) angle_change = -elapsed * angle_change_per_second;
            // Log::log(Log::INFO, "cur = {} ang = {}, change = {}\n", m_rotation, angle, angle_change);
            m_rotation += angle_change;
            set_rotation(m_rotation + 90);
            // Log::log(Log::INFO, "move vector = ({}, {})\n", m_speed * elapsed * std::cos(angle_rad), m_speed * elapsed * std::sin(angle_rad));
            float dangle = m_rotation * M_PI / 180;
            move(speed_boost * m_speed * elapsed * std::cos(dangle),
                    speed_boost * m_speed * elapsed * std::sin(dangle));
        }
    } else {
        auto angle = -90;
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
        
        float angle_change_per_second = 45.f * 4;
        if(angle_change > elapsed * angle_change_per_second) angle_change = elapsed * angle_change_per_second;
        if(angle_change < -elapsed * angle_change_per_second) angle_change = -elapsed * angle_change_per_second;
        // Log::log(Log::INFO, "cur = {} ang = {}, change = {}\n", m_rotation, angle, angle_change);
        m_rotation += angle_change;
        set_rotation(m_rotation + 90);
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

bool BaseEnemy::path_end() {
    if(m_path_end) return true;
    return m_path_end = (std::abs(m_rotation - 270.f) < 0.001f and m_current_goal == m_goals.size());
}

void BaseEnemy::deal_dmg(uint dmg) {
    m_hp -= std::min(m_hp, dmg);
}

void BaseEnemy::move_right(float elapsed) {
    move(m_speed * elapsed * 0.3f, 0);
}

void BaseEnemy::move_left(float elapsed) {
    move(-m_speed * elapsed * 0.3f, 0);
}

thread_local std::mt19937 gen{std::random_device{}()};
template <typename T>
T random(T min, T max) {
    using dist = std::conditional_t<std::is_integral<T>::value, 
                    std::uniform_int_distribution<T>, 
                    std::uniform_real_distribution<T>>;
    return dist{min, max}(gen);
}
	

void BaseEnemy::move_random_down(float elapsed) {
    if(m_sprite.getPosition().y > 1180) {
        set_position(m_sprite.getPosition().x, -100);

        float dx = random(50.f, 300.f);
        if(random(0.f, 1.f) < 0.5f) {
            dx = -dx;
        }
        m_random_goal_x = m_sprite.getPosition().x + dx;
        return;
    }

    if(m_sprite.getPosition().x < -50) {
        set_position(1920 + 50, m_sprite.getPosition().y);
    }

    if(m_sprite.getPosition().x > 1920 + 50) {
        set_position(-50, m_sprite.getPosition().y);
    }

    if(m_random_goal_x < 0 or abs(m_random_goal_x - m_sprite.getPosition().x) < 0.5) {
        float dx = random(50.f, 300.f);
        if(random(0.f, 1.f) < 0.5f) {
            dx = -dx;
        }
        m_random_goal_x = m_sprite.getPosition().x + dx;
    }

    float dx = m_random_goal_x - m_sprite.getPosition().x;
    if(dx < 0) {
        dx = -dx;
        dx = std::min(dx, elapsed * m_speed);
        dx = -dx;
    } else {
        dx = std::min(dx, elapsed * m_speed);
    }
    
    move(dx, random(0.8f, 1.f) * elapsed * m_speed);
}

BaseEnemy::BaseEnemy(std::vector<sf::Vector2f> goals, float time_offset, float speed, uint hp, const std::string texture_path) 
    :   m_goals{goals}, 
        m_current_goal{1}, 
        m_time_offset{time_offset}, 
        m_current_time{0}, 
        m_speed{speed}, 
        m_hp{hp},
        m_rotation{90},
        m_path_end{false}, 
        m_random_goal_x{-10}
    {
    set_texture(texture_path);
    set_position(goals.at(0));
    set_rotation(0);
}