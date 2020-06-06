#pragma once
#include "BaseScreen.hpp"
#include "GameScreen.hpp"

class ScreenManager {
private:
    static BaseScreen* current_screen;
    static GameScreen* game_screen;
public:
    static void draw(sf::RenderWindow& window);
    static void update(sf::RenderWindow& window, float time_diff);
    static void handle_event(sf::RenderWindow& window, sf::Event event);
    static void setup();

    ScreenManager();
    ~ScreenManager();
};