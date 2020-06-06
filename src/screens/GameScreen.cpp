#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
    std::cerr << "DRAW GAME\n";
}

void GameScreen::update(sf::RenderWindow& window, float time_diff) {
    std::cerr << "UPDATE GAME\n";
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    std::cerr << "HANDLE GAME\n";
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            // ScreenManager::load_screen("MenuScreen");
        }
    }
}