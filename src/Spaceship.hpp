#pragma once
#include <SFML/Graphics.hpp>
#include "colliders/ConvexColliders.hpp"

class Spaceship : public sf::Drawable , public ConvexColliders {
protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    void set_texture(const std::string path);
    void set_position(float x, float y);
    void set_position(sf::Vector2f pos);
    void set_origin(float x, float y);
    void set_origin(sf::Vector2f pos);
    void move(float x, float y);
    void move(sf::Vector2f offset);

    Spaceship();
};