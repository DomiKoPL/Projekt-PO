#include "PowerUp.hpp"
#include "TextureManager.hpp"
#include "colliders/ColliderMaker.hpp"

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void PowerUp::update(float elapsed) {
    move(0, m_speed * elapsed);
    m_sprite.move(0, m_speed * elapsed);
}

void PowerUp::change(Player& player) {
    if(m_type == PowerUpType::SPEED) {
        player.add_speed(20);
    } else if(m_type == PowerUpType::BULLETS) {
        player.increase_shoot_speed();
    } else if(m_type == PowerUpType::WEAPONUPGRADE) {
        player.upgrade_weapon();
    }
    m_used = true;  
}

#include "Log.hpp"

bool PowerUp::is_dead() const {
    auto [x, y] = m_sprite.getPosition();
    Log::log(Log::INFO, "Power = {} {} {}\n", int(m_used), x, y);
    if(m_used) return true;
    return (x < -100 or x > 2020 or y < - 30 or y > 1180);
}

PowerUp::PowerUp() {

}

PowerUp::PowerUp(PowerUpType type, sf::Vector2f position) : m_type{type}, m_speed{300}, m_used{false} {
    std::string path;
    if(m_type == PowerUpType::SPEED) {
        path = "Resources/Space Shooter - 1/Item/PowerUp5.png";
    } else if(m_type == PowerUpType::BULLETS) {
        path = "Resources/Space Shooter - 1/Item/PowerUp2.png";
    } else if(m_type == PowerUpType::WEAPONUPGRADE) {
        path = "Resources/Space Shooter - 1/Item/PowerUp1.png";
    }   

    auto& texture = TextureManager::instance().get_texture(path);
    m_sprite.setTexture(texture);
    auto [width, height] = texture.getSize();
    float scale = 50.f / width;
    m_sprite.setScale(scale, scale);
    m_sprite.setOrigin(width / 2.f, height / 2.f);

    m_sprite.setPosition(position);
    ConvexColliders::set_colliders(ColliderMaker::make_collider(texture.copyToImage(), 2, {scale, scale}));
    ConvexColliders::set_position(position);
    ConvexColliders::set_origin(sf::Vector2f{width / 2.f, height / 2.f} * scale);
}