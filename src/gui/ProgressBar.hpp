#pragma once
#include <SFML/Graphics.hpp>

class ProgressBar : public sf::Drawable, public sf::Transformable {
private:
    sf::Sprite m_box, m_fill;
    float m_min, m_max;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void update(float val);
    ProgressBar();
    ProgressBar(float min, float max);
    void set_size(float width, float height);
};