#pragma once
#include "BaseScreen.hpp"
#include "../gui/Button.hpp"

class OptionsScreen : public BaseScreen {
private:

    std::vector<std::reference_wrapper<Button>> m_buttons;
public:
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, float elapsed);
    void handle_event(sf::RenderWindow& window, sf::Event event);
    OptionsScreen();
    ~OptionsScreen();
};