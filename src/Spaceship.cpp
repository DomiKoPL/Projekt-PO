#include "Spaceship.hpp"

void Spaceship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::CircleShape shape;
    shape.setPosition({100, 100});
    shape.setRadius(50);
    target.draw(shape);
}