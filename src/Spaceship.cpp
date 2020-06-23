#include "Spaceship.hpp"
#include "Log.hpp"
#include "colliders/ColliderMaker.hpp"

void Spaceship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Log::log(Log::INFO, "Spaceship draw\n");
    target.draw(m_sprite);
    // ConvexColliders::draw(target, states);
}

void Spaceship::set_texture(const std::string path) {
    if(not m_texture.loadFromFile(path)) {
        Log::log(Log::ERROR, "Spaceship texture loading error!\n");
    }
    m_texture.setSmooth(true); // TODO: test which is better
    m_sprite.setTexture(m_texture);
    float scale = 60.f / m_texture.getSize().x;
    auto[width, height] = m_texture.getSize();
    m_sprite.setOrigin(width / 2, 0);
    m_sprite.setScale(scale, scale);
    
    ConvexColliders::set_colliders(ColliderMaker::make_collider(m_texture.copyToImage(), 3, {scale, scale}));
    ConvexColliders::set_origin(sf::Vector2f{width / 2.f, 0.f} * scale);
}

void Spaceship::set_position(float x, float y) {
    set_position({x, y});
}

void Spaceship::set_position(sf::Vector2f pos) {
    move(pos - m_sprite.getPosition());
}

void Spaceship::set_origin(float x, float y) {
    set_origin({x, y});
}

void Spaceship::set_origin(sf::Vector2f origin) {
    m_sprite.setOrigin(origin);
    ConvexColliders::set_origin(origin);
}

void Spaceship::move(float x, float y) {
    move({x, y});
}

void Spaceship::move(sf::Vector2f offset) {
    m_sprite.move(offset);
    ConvexColliders::move(offset);
}

Spaceship::Spaceship() {

}