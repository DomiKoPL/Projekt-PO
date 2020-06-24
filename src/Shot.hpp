#pragma once
#include <SFML/Graphics.hpp>
#include "colliders/ConvexColliders.hpp"

class Shot : public sf::Drawable, public ConvexColliders {
private:
    float m_angle;
    float m_speed;
    uint m_damage;
    uint m_penetration; 
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    void update(float elapsed);
    uint get_damage() const;
    bool is_dead() const;
    void shot();
    Shot(float angle, float speed, uint damage, uint penetration, std::string texture_path, sf::Vector2f pos, float size);
};