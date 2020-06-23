#pragma once
#include <SFML/Graphics.hpp>
#include "BaseScreen.hpp"
#include "../Player.hpp"
#include "../gui/Button.hpp"

class GameScreen : public BaseScreen {
private:
    Player m_player;
    sf::Texture m_background_texture;
    sf::Sprite m_background_sprite;
    sf::Texture m_level_texture;
    sf::Sprite m_level_sprite;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);

    GameScreen();
};