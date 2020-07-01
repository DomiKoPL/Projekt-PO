#pragma once
#include <SFML/Graphics.hpp>
#include "BaseScreen.hpp"
#include "../Player.hpp"
#include "../gui/Button.hpp"
#include "../levels/LevelManager.hpp"
#include "../MusicManager.hpp"

class GameScreen : public BaseScreen {
private:
    Player m_player;
    
    sf::Texture m_level_texture;
    sf::Sprite m_level_sprite;

    sf::Sprite m_player_life_sprite;
    
    LevelManager m_level_manager;

    sf::Sprite m_game_over;
    sf::Texture m_press_space_texture;
    sf::Sprite m_press_space;
    float m_time_from_death;

    bool m_pause;

    Button m_menu;
    Button m_resume;
    sf::Sprite m_pause_sprite;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
    void reset();

    GameScreen();
};