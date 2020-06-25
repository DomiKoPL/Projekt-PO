#pragma once
#include "BaseScreen.hpp"
#include "../gui/Button.hpp"

class MainMenuScreen : public BaseScreen {
private:
    Button play_button;
    Button exit_button;
    Button options_button;
    std::vector<std::reference_wrapper<Button>> m_buttons;

    sf::Texture m_background_texture;
    sf::Sprite m_background_sprite;
    float m_background_move_speed = 10.f;
    float m_background_current_y = 0.f;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
    void reset();
    MainMenuScreen();
    ~MainMenuScreen();
};