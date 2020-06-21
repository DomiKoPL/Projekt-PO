#pragma once
#include "ConvexCollider.hpp"
#include <vector>

class ConvexColliders {
private:
    std::vector<ConvexCollider*> colliders;

public:
    ConvexColliders();
    ConvexColliders(std::vector<sf::Vector2f> vertices, sf::Vector2f postion, sf::Vector2f origin);
    ConvexColliders(std::vector<std::vector<sf::Vector2f>> vertices, sf::Vector2f postion, sf::Vector2f origin);

    void add_collider(std::vector<sf::Vector2f> vertices, sf::Vector2f position, sf::Vector2f origin);
    void add_collider(ConvexCollider* collider);
    void set_colliders(ConvexColliders* collider);

    bool is_colliding_with(ConvexCollider& collider);
    bool is_colliding_with(ConvexCollider *collider);
    bool is_colliding_with(ConvexColliders& collider);
    bool is_colliding_with(ConvexColliders *collider);

    void set_position(sf::Vector2f position);
    void move(float x, float y);
    void move(sf::Vector2f offset);

    void set_rotation(float rotation);
    void rotate(float offset);

    void set_origin(sf::Vector2f origin);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void reset_color();
};