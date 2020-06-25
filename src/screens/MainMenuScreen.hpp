#pragma once
#include "BaseScreen.hpp"
#include "../gui/Button.hpp"
#include "../levels/LevelManager.hpp"

class MainMenuScreen : public BaseScreen {
private:
    Button play_button;
    Button exit_button;
    Button options_button;
    std::vector<std::reference_wrapper<Button>> m_buttons;

    sf::Texture m_name_texture;
    sf::Sprite m_name;
    LevelManager m_level_manager;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
    void reset();
    MainMenuScreen();
    ~MainMenuScreen();
};