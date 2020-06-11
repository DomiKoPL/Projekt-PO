#pragma once
#include "BaseScreen.hpp"
#include "../gui/Button.hpp"

class MainMenuScreen : public BaseScreen {
private:
    Button play_button;
    Button exit_button;
    Button options_button;
    std::vector<std::reference_wrapper<Button>> m_buttons;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
    MainMenuScreen();
    ~MainMenuScreen();
};