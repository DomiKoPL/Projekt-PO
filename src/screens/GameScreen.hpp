#pragma once
#include <SFML/Graphics.hpp>
#include "BaseScreen.hpp"
#include "../Player.hpp"
#include "../gui/Button.hpp"
#include "../levels/LevelManager.hpp"

class GameScreen : public BaseScreen {
private:
    Player m_player;
    sf::Texture m_background_texture;
    sf::Sprite m_background_sprite;
    sf::Texture m_level_texture;
    sf::Sprite m_level_sprite;

    sf::Sprite m_player_life_sprite;

    float m_background_move_speed = 10.f;
    float m_background_current_y = 0.f;
    LevelManager m_level_manager;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);

    GameScreen();
};