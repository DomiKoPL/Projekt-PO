#include "ScreenManager.hpp"
#include "GameScreen.hpp"
#include "MainMenuScreen.hpp"
#include "OptionsScreen.hpp"
#include "../Log.hpp"

void ScreenManager::draw(sf::RenderWindow& window) {
    if(close_window) {
        window.close();
    }
    current_screen->draw(window);
}

void ScreenManager::update(sf::RenderWindow& window, float elapsed) {
    current_screen->update(window, elapsed);
}

void ScreenManager::handle_event(sf::RenderWindow& window, sf::Event event) {
    current_screen->handle_event(window, event);
}

void ScreenManager::setup() {
    screens["GameScreen"] = new GameScreen();
    screens["MainMenuScreen"] = new MainMenuScreen();
    screens["OptionsScreen"] = new OptionsScreen();

    set_screen("MainMenuScreen");
}

void ScreenManager::clear() {
    for(auto it : screens) {
        delete it.second;
    }
}

void ScreenManager::set_screen(const std::string screen_name) {
    if(not screens.count(screen_name)) {
        Log::log(Log::ERROR, "Screen \"{}\" not found!\n", screen_name);
    }
    current_screen = screens[screen_name];
    current_screen->reset();
}

void ScreenManager::close() {
    close_window = true;
}