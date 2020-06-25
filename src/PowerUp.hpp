#pragma once
#include "Player.hpp"
#include "colliders/ConvexColliders.hpp"

enum PowerUpType {
    SPEED, BULLETS, WEAPONUPGRADE
};

class PowerUp : public sf::Drawable, public ConvexColliders {
private:
    PowerUpType m_type;
    float m_speed;
    sf::Sprite m_sprite;
    bool m_used;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void update(float elapsed);
    void change(Player& player);
    bool is_dead() const;
    PowerUp();
    PowerUp(PowerUpType type, sf::Vector2f position);
};