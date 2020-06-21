#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class ConvexCollider : public sf::Drawable {
private:
    sf::Vector2f position;
    float rotation;
    sf::Vector2f origin;
    std::vector<sf::Vector2f> normals;
    std::vector<sf::Vector2f> vertices;

    sf::Vector2f centroid;
    float radius;
    int collision;

    sf::Color shape_color;

     void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    ConvexCollider();
    ConvexCollider(sf::Vector2f position);
    ConvexCollider(sf::Vector2f position, sf::Vector2f origin);
    ConvexCollider(std::vector<sf::Vector2f> vertices, sf::Vector2f position, sf::Vector2f origin);
    
    const std::vector<sf::Vector2f>& get_normals() const;
    std::pair<float, float> get_minmax_along(sf::Vector2f vector) const;

    bool is_colliding_with(ConvexCollider& collider);
    bool is_colliding_with(ConvexCollider *collider) const;

    void set_position(sf::Vector2f position);
    void move(sf::Vector2f offset);
    sf::Vector2f get_position() const;

    void set_rotation(float rotation);
    void rotate(float offset);
    float get_rotation() const;

    void set_origin(sf::Vector2f origin);
    sf::Vector2f get_origin() const;

    void reset_color();
    
protected:
    void update_normals();
    void calc_centroid();
};