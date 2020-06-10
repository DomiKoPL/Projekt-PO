#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"
#include "../Log.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
    Log::log(Log::INFO, "DRAW GAME\n");
}

void GameScreen::update(sf::RenderWindow& window, float elapsed) {
    Log::log(Log::INFO, "UPDATE GAME\n");
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    Log::log(Log::INFO, "HANDLE GAME\n");

    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            // to jest nic ciekawego
        }
    }
}