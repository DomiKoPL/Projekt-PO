#include "Shot.hpp"
#include "colliders/ColliderMaker.hpp"
#include <math.h>

// TODO: to nie dziala

void Shot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
    // ConvexColliders::draw(target, states);
}

void Shot::update(float elapsed) {
    float x = cos(M_PI * (m_angle - 90.f) / 180.f) * m_speed * elapsed;
    float y = sin(M_PI * (m_angle - 90.f) / 180.f) * m_speed * elapsed;
    m_sprite.move(x, y);
    ConvexColliders::move(x, y);
}

uint Shot::get_damage() const {
    return m_damage;
}

bool Shot::is_dead() const {
    if(m_penetration == 0) {
        return true;
    }
    auto [x, y] = m_sprite.getPosition();
    if(-90 <= m_angle and m_angle <= 90) {
        return (x < -100 or x > 2020 or y < -30);
    }
    return (x < -100 or x > 2020 or y > 1180);
}

void Shot::shot() {
    // TODO: dangerous
    m_penetration--;
}

Shot::Shot(float angle, float speed, uint damage, uint penetration, std::string texture_path, sf::Vector2f pos, float size) {
    m_angle = angle;
    m_speed = speed;
    m_damage = damage;
    m_penetration = penetration;

    m_texture.loadFromFile(texture_path);
    auto tex_size = sf::Vector2f(m_texture.getSize());
    float scale = size / tex_size.x;
    
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(scale, scale);
    ConvexColliders::set_colliders(ColliderMaker::make_collider(m_texture.copyToImage(), 1, {scale, scale}));

    m_sprite.setPosition(pos);
    ConvexColliders::set_position(pos);
    
    m_sprite.setOrigin(tex_size / 2.f);
    ConvexColliders::set_origin(tex_size / 2.f * scale); //! yes, you are right, this is shit..

    m_sprite.rotate(angle);
    ConvexColliders::rotate(angle);
    
}