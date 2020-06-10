#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button : public sf::Drawable, public sf::Transformable {
private:
    sf::Texture m_texture, m_highlight_texture;
    sf::Sprite m_sprite;
    std::function<void()> m_func_when_clicked;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    void load_texture(const std::string path);
    void load_highlight_texture(const std::string path);
    void add_function_when_clicked(std::function<void()> func);
    void update(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, sf::Event event);

    // height will be calucated automatically
    void set_width(float width);
    // width will be calucated automatically
    void set_height(float height);
    void set_size(float width, float height);
    void set_size(sf::Vector2f size);
};