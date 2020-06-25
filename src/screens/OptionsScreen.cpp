#include "OptionsScreen.hpp"
#include "ScreenManager.hpp"
#include "../Log.hpp"
#include "../Settings.hpp"

void OptionsScreen::draw(sf::RenderWindow& window) {
    // Log::log(Log::INFO, "DRAW Options\n");
    for(auto& button : m_buttons) {
        window.draw(button.get());
    }
}

void OptionsScreen::update(sf::RenderWindow& window, float elapsed) {
    // Log::log(Log::INFO, "UPDATE Options\n");
    for(auto& button : m_buttons) {
        button.get().update(window);
    }
}

void OptionsScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE Options\n");
    for(auto& button : m_buttons) {
        button.get().update(window, event);
    }
}

void OptionsScreen::reset() {

}

OptionsScreen::OptionsScreen() {
    
}

OptionsScreen::~OptionsScreen() {

}