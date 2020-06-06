#include "ScreenManager.hpp"

BaseScreen* ScreenManager::current_screen;
GameScreen* ScreenManager::game_screen;

void ScreenManager::draw(sf::RenderWindow& window) {
    current_screen->draw(window);
}

void ScreenManager::update(sf::RenderWindow& window, float time_diff) {
    current_screen->update(window, time_diff);
}

void ScreenManager::handle_event(sf::RenderWindow& window, sf::Event event) {
    current_screen->handle_event(window, event);
}

void ScreenManager::setup() {
    game_screen = new GameScreen();

    current_screen = game_screen;
}