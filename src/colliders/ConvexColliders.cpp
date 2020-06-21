#include "ConvexColliders.hpp"

ConvexColliders::ConvexColliders() {

}

ConvexColliders::ConvexColliders(std::vector<sf::Vector2f> vertices, sf::Vector2f postion, sf::Vector2f origin) {
    add_collider(vertices, postion, origin);
}

ConvexColliders::ConvexColliders(std::vector<std::vector<sf::Vector2f>> vertices, sf::Vector2f postion, sf::Vector2f origin) {
    for(auto& ver : vertices) {
        add_collider(ver, postion, origin);
    }
}

void ConvexColliders::add_collider(std::vector<sf::Vector2f> vertices, sf::Vector2f postion, sf::Vector2f origin) {
    colliders.push_back(new ConvexCollider(vertices, postion, origin));
}

bool ConvexColliders::is_colliding_with(ConvexCollider& collider) {
    for(auto& coll : this->colliders) {
        if(coll->is_colliding_with(collider)) {
            return true;
        }
    }
    return false;
}

bool ConvexColliders::is_colliding_with(ConvexCollider *collider) {
    for(auto& coll : this->colliders) {
        if(coll->is_colliding_with(collider)) {
            return true;
        }
    }
    return false;
}

bool ConvexColliders::is_colliding_with(ConvexColliders& collider) {
    for(auto& coll : this->colliders) {
        if(collider.is_colliding_with(coll)) {
            return true;
        }
    }
    return false;
}

bool ConvexColliders::is_colliding_with(ConvexColliders *collider) {
    for(auto& coll : this->colliders) {
        if(collider->is_colliding_with(coll)) {
            return true;
        }
    }
    return false;
}

void ConvexColliders::set_position(sf::Vector2f position) {
    for(auto& collider : this->colliders) {
        collider->set_position(position);
    }
}

void ConvexColliders::move(sf::Vector2f offset) {
    for(auto& collider : this->colliders) {
        collider->move(offset);
    }
}

void ConvexColliders::set_rotation(float rotation) {
    for(auto& collider : this->colliders) {
        collider->set_rotation(rotation);
    }
}

void ConvexColliders::rotate(float offset) {
    for(auto& collider : this->colliders) {
        collider->rotate(offset);
    }
}

void ConvexColliders::set_origin(sf::Vector2f origin) {
    for(auto& collider : this->colliders) {
        collider->set_origin(origin);
    }
}

void ConvexColliders::draw(sf::RenderWindow& window) const {
    for(auto& collider : this->colliders) {
        collider->draw(window);
    }
}

void ConvexColliders::reset_color() {
    for(auto& collider : this->colliders) {
        collider->reset_color();
    }
}
