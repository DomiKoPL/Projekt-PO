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
        player.add_speed(50);
    } else if(m_type == PowerUpType::BULLETSUPGRADE) {
        player.add_shoot_speed(-0.05f);
    } else if(m_type == PowerUpType::BULLETSDOWNGRADE) {
        player.add_shoot_speed(0.05f);
    } else if(m_type == PowerUpType::WEAPONUPGRADE) {
        player.upgrade_weapon();
    } else if(m_type == PowerUpType::SLOW) {
        player.add_speed(-50);
    } else if(m_type == PowerUpType::WEAPONDOWNGRADE) {
        player.downgrade_weapon();
    } else if(m_type == PowerUpType::LIFE) {
        player.add_life();
    }

    m_used = true;  
}


bool PowerUp::is_dead() const {
    if(m_used) return true;
    auto [x, y] = m_sprite.getPosition();
    return (x < -100 or x > 2020 or y < - 30 or y > 1180);
}

PowerUp::PowerUp() {

}

PowerUp::PowerUp(PowerUpType type, sf::Vector2f position) : m_type{type}, m_speed{300}, m_used{false} {
    std::string path;
    if(m_type == PowerUpType::SPEED) {
        path = "Resources/Space Shooter - 1/Item/PowerUp5.png";
    } else if(m_type == PowerUpType::BULLETSUPGRADE) {
        path = "Resources/Space Shooter - 1/Item/PowerUp9.png";
    } else if(m_type == PowerUpType::BULLETSDOWNGRADE) {
        path = "Resources/Space Shooter - 1/Item/PowerUp10.png";
        m_speed = 500; 
    } else if(m_type == PowerUpType::WEAPONUPGRADE) {
        path = "Resources/Space Shooter - 1/Item/PowerUp8.png";
    } else if(m_type == PowerUpType::SLOW) {
        path = "Resources/Space Shooter - 1/Item/PowerUp6.png";
        m_speed = 500;
    } else if(m_type == PowerUpType::WEAPONDOWNGRADE) {
        path = "Resources/Space Shooter - 1/Item/PowerUp1.png";
        m_speed = 500;
    } else if(m_type == PowerUpType::LIFE) {
        path = "Resources/Space Shooter - 1/HUD/LifeIcon.png";
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