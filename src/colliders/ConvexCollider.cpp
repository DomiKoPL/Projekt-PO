#include "ConvexCollider.hpp"
#include <math.h>
#include <iostream>
#include <random>

ConvexCollider::ConvexCollider()
    : position({0, 0}), rotation(0), origin({0, 0})
{
    shape_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

ConvexCollider::ConvexCollider(sf::Vector2f position)
    : position(position), rotation(0), origin({0, 0})
{
    shape_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

ConvexCollider::ConvexCollider(sf::Vector2f position, sf::Vector2f origin)
    : position(position), rotation(0), origin(origin)
{
    shape_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

ConvexCollider::ConvexCollider(std::vector<sf::Vector2f> vertices, sf::Vector2f position, sf::Vector2f origin)
    : position(position), rotation(0), origin(origin), vertices(vertices)
{
    shape_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    normals.resize(vertices.size());
    update_normals();
    calc_centroid();
}

const std::vector<sf::Vector2f> &ConvexCollider::get_normals() const {
    return this->normals;
}

std::pair<float, float> ConvexCollider::get_minmax_along(sf::Vector2f vector) const {
    std::pair<float, float> res = {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::lowest()};
    float vector_magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);

    for (auto vertex : vertices) {
        //* change coordinates to global
        vertex += position;
        float dot_product = vertex.x * vector.x + vertex.y * vector.y;
        float vertex_cast = dot_product / vector_magnitude;

        res.first = std::min(res.first, vertex_cast);
        res.second = std::max(res.second, vertex_cast);
    }

    return res;
}

bool ConvexCollider::is_colliding_with(ConvexCollider &collider) {
    float dx = position.x + centroid.x - (collider.position.x + collider.centroid.x);
    float dy = position.y + centroid.y - (collider.position.y + collider.centroid.y);
    if (dx * dx + dy * dy > (radius + collider.radius) * (radius + collider.radius)) {
        return false;
    }
    collision = std::max(collision, 1);
    collider.collision = std::max(collider.collision, 1);

    for (auto &normal : this->normals) {
        auto [min1, max1] = get_minmax_along(normal);
        auto [min2, max2] = collider.get_minmax_along(normal);

        if (min1 > max2 or max1 < min2) {
            return false;
        }
    }

    auto &normals2 = collider.get_normals();
    for (auto &normal : normals2) {
        auto [min1, max1] = get_minmax_along(normal);
        auto [min2, max2] = collider.get_minmax_along(normal);

        if (min1 > max2 or max1 < min2) {
            return false;
        }
    }

    // std::cerr << "Collision" << std::endl;
    collision = 2;
    collider.collision = 2;
    return true;
}

bool ConvexCollider::is_colliding_with(ConvexCollider *collider) const {
    float dx = position.x + centroid.x - (collider->position.x + collider->centroid.x);
    float dy = position.y + centroid.y - (collider->position.y + collider->centroid.y);
    if (dx * dx + dy * dy > (radius + collider->radius) * (radius + collider->radius)) {
        return false;
    }

    for (auto &normal : this->normals) {
        auto [min1, max1] = get_minmax_along(normal);
        auto [min2, max2] = collider->get_minmax_along(normal);

        if (min1 > max2 or max1 < min2) {
            return false;
        }
    }

    auto &normals2 = collider->get_normals();
    for (auto &normal : normals2) {
        auto [min1, max1] = get_minmax_along(normal);
        auto [min2, max2] = collider->get_minmax_along(normal);

        if (min1 > max2 or max1 < min2) {
            return false;
        }
    }

    return true;
}

void ConvexCollider::set_position(sf::Vector2f position) {
    this->position = position;
}

void ConvexCollider::move(sf::Vector2f offset) {
    this->position += offset;
}

sf::Vector2f ConvexCollider::get_position() const {
    return this->position;
}

void ConvexCollider::set_rotation(float rotation) {
    rotate(rotation - this->rotation);
}

void ConvexCollider::rotate(float offset) {
    this->rotation += offset;

    //* normalize rotation
    while (this->rotation >= 360.0) {
        this->rotation -= 360.0;
    }
    while (this->rotation < 0.0) {
        this->rotation += 360.0;
    }

    float rad = offset / 180.0 * M_PI;

    for (auto &vertex : this->vertices) {
        vertex -= get_origin();
        sf::Vector2f new_position;
        new_position.x = vertex.x * std::cos(rad) - vertex.y * std::sin(rad);
        new_position.y = vertex.y * std::cos(rad) + vertex.x * std::sin(rad);
        vertex = new_position + get_origin();
    }

    centroid -= get_origin();
    sf::Vector2f new_position;
    new_position.x = centroid.x * std::cos(rad) - centroid.y * std::sin(rad);
    new_position.y = centroid.y * std::cos(rad) + centroid.x * std::sin(rad);
    centroid = new_position + get_origin();

    update_normals();
}

float ConvexCollider::get_rotation() const {
    return this->rotation;
}

void ConvexCollider::set_origin(sf::Vector2f origin) {
    this->origin = origin;
}

sf::Vector2f ConvexCollider::get_origin() const {
    return this->origin;
}   

void ConvexCollider::draw(sf::RenderWindow &window) const {
    sf::ConvexShape shape;

    shape.setPosition(position);
    shape.setPointCount(vertices.size());

    for (int i = 0; i < int(vertices.size()); ++i) {
        shape.setPoint(i, vertices[i]);
    }

    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setOrigin({radius, radius});
    circle.setPosition(position + centroid);

    if(collision == 2) {
        // shape.setFillColor(shape_color);
        shape.setFillColor(sf::Color::Red);
        circle.setFillColor(sf::Color::Blue);
        // window.draw(circle);
        window.draw(shape);
    } else if(collision == 1) {
        shape.setFillColor(shape_color);
        // shape.setFillColor(sf::Color::Cyan);
        circle.setFillColor(sf::Color::Yellow);
        // window.draw(circle);
        window.draw(shape);
    } else {
        shape.setFillColor(shape_color);
        // shape.setFillColor(sf::Color::Cyan);
        circle.setFillColor(sf::Color::Blue);
        // window.draw(circle);
        window.draw(shape);
    }
}

void ConvexCollider::update_normals() {
    normals[0].x = vertices[0].y - vertices[int(vertices.size()) - 1].y;
    normals[0].y = -vertices[0].x + vertices[int(vertices.size()) - 1].x;

    for (int i = 0; i < int(vertices.size()) - 1; i++) {
        normals[i + 1].x = vertices[i + 1].y - vertices[i].y;
        normals[i + 1].y = -vertices[i + 1].x + vertices[i].x;
    }
}

void ConvexCollider::calc_centroid() {
    float signed_area = 0.0;

    for (int i = 0; i < int(vertices.size()) - 1; i++) {
        auto [x0, y0] = vertices[i];
        auto [x1, y1] = vertices[i + 1];
        float cross_product = x0 * y1 - x1 * y0;
        signed_area += cross_product;
        centroid.x += (x0 + x1) * cross_product;
        centroid.y += (y0 + y1) * cross_product;
    }

    auto [x0, y0] = vertices[int(vertices.size()) - 1];
    auto [x1, y1] = vertices[0];
    float cross_product = x0 * y1 - x1 * y0;
    signed_area += cross_product;
    centroid.x += (x0 + x1) * cross_product;
    centroid.y += (y0 + y1) * cross_product;

    signed_area /= 2.0;

    centroid.x /= (6.0 * signed_area);
    centroid.y /= (6.0 * signed_area);
    
    radius = 0.0;
    for (auto vertex : vertices) {
        float dx = vertex.x - centroid.x;
        float dy = vertex.y - centroid.y;
        radius = std::max(radius, sqrt(dx * dx + dy * dy));
    }
}

void ConvexCollider::reset_color() {
    collision = 0;
}