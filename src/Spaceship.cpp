#include "Spaceship.hpp"
#include "Log.hpp"
#include "colliders/ColliderMaker.hpp"

void Spaceship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Log::log(Log::INFO, "Spaceship draw\n");
    target.draw(m_sprite);
    ConvexColliders::draw(target, states);
}

void Spaceship::set_texture(const std::string path) {
    if(not m_texture.loadFromFile(path)) {
        Log::log(Log::ERROR, "Spaceship texture loading error!\n");
    }
    m_sprite.setTexture(m_texture);
    
    ConvexColliders::set_colliders(ColliderMaker::make_collider(m_texture.copyToImage(), 3));
}

void Spaceship::set_position(float x, float y) {
    set_position({x, y});
}

void Spaceship::set_position(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
    ConvexColliders::set_position(pos);
}

void Spaceship::set_origin(float x, float y) {
    set_origin({x, y});
}

void Spaceship::set_origin(sf::Vector2f origin) {
    m_sprite.setOrigin(origin);
    ConvexColliders::set_origin(origin);
}

void Spaceship::move_left(float elapsed) {
    m_sprite.move(-m_move_speed * elapsed, 0);
    ConvexColliders::move(-m_move_speed * elapsed, 0);
}

void Spaceship::move_right(float elapsed) {
    m_sprite.move(m_move_speed * elapsed, 0);
    ConvexColliders::move(m_move_speed * elapsed, 0);
}

Spaceship::Spaceship() {

}