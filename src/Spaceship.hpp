#pragma once
#include <SFML/Graphics.hpp>

class Spaceship : public sf::Drawable {

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};