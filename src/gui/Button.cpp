#include "Button.hpp"
#include "../Log.hpp"

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Button::load_texture(const std::string path) {
    if(not m_texture.loadFromFile(path)) {
        Log::log(Log::ERROR, "Button texture error, path = {}\n", path);
    }
    m_sprite.setTexture(m_texture);
}

void Button::load_highlight_texture(const std::string path) {
    if(not m_highlight_texture.loadFromFile(path)) {
        Log::log(Log::ERROR, "Button texture error, path = {}\n", path);
    }
}

void Button::add_function_when_clicked(std::function<void()> func) {
    m_func_when_clicked = func;
}

void Button::update(sf::RenderWindow& window) {
    auto roz = sf::Vector2f(m_sprite.getTexture()->getSize());
    m_sprite.setOrigin(roz / 2.f);

    if(size.x != 0 and size.y != 0) {
        auto window_size = window.getSize();
        auto sprite_size = m_sprite.getTexture()->getSize();

        sf::Vector2f scale = {size.x / sprite_size.x * window_size.x / 1920.f, 
                                size.y / sprite_size.y * window_size.y / 1080.f};
                                
        if(m_sprite.getScale() != scale) {
            m_sprite.setScale(scale);
        }
    } else if(size.x != 0) {
        auto window_size = window.getSize();
        auto sprite_size = m_sprite.getTexture()->getSize();

        sf::Vector2f scale = {size.x / sprite_size.x * window_size.x / 1920.f, 
                                size.x / sprite_size.x * window_size.x / 1920.f};

        if(m_sprite.getScale() != scale) {
            m_sprite.setScale(scale);
        }
    } else if(size.y != 0) {
        auto window_size = window.getSize();
        auto sprite_size = m_sprite.getTexture()->getSize();

        sf::Vector2f scale = {size.y / sprite_size.y * window_size.y / 1080.f, 
                                size.y / sprite_size.y * window_size.y / 1080.f};

        if(m_sprite.getScale() != scale) {
            m_sprite.setScale(scale);
        }
    }


    // no highlight texture
    if(m_highlight_texture.getSize() == sf::Vector2u(0, 0)) {
        return;
    }

    auto[x, y] = sf::Mouse::getPosition(window);

    if(getTransform().transformRect(m_sprite.getGlobalBounds()).contains(x, y)) {
        if(m_sprite.getTexture() != &(m_highlight_texture)) {
            m_sprite.setTexture(m_highlight_texture);
            Log::log(Log::INFO, "Changing button texture to highlight\n");
        }   
    } else {
        if(m_sprite.getTexture() != &(m_texture)) {
            m_sprite.setTexture(m_texture);
            Log::log(Log::INFO, "Changing button texture to normal\n");
        }   
    }
}

void Button::update(sf::RenderWindow& window, sf::Event event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Left) {
            auto[x, y] = sf::Mouse::getPosition(window);
            if(getTransform().transformRect(m_sprite.getGlobalBounds()).contains(x, y)) {
                m_func_when_clicked();
            }
        }
    }
}

void Button::set_width(float width) {
    size.x = width;
}

void Button::set_height(float height) {
    size.y = height;
}

void Button::set_size(float width, float height) {
    set_size({width, height});
}

void Button::set_size(sf::Vector2f size) {
    this->size = size;
}