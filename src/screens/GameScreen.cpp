#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"
#include "../Log.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
    // Log::log(Log::INFO, "DRAW GAME\n");
    // m_player.draw_collider(window);
    window.draw(m_player);
}

void GameScreen::update(sf::RenderWindow& window, float elapsed) {
    // Log::log(Log::INFO, "UPDATE GAME {} \n", 1.0 / elapsed);
    m_player.update(elapsed);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_player.move_left(elapsed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_player.move_right(elapsed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_player.shoot();
    }
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE GAME\n");

    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            // to jest nic ciekawego
        }
    }
}

GameScreen::GameScreen() {
    m_player.set_texture("Resources/Space Shooter - 1/Ship/2.png");
    m_player.set_position(1920.f / 2, 1080.f - 80.f);
}