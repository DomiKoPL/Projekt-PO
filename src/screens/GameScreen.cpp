#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"
#include "../gui/TextGenerator.hpp"
#include "../Log.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(m_background_sprite);
    
    m_level_manager.draw(window);
    // Log::log(Log::INFO, "DRAW GAME\n");
    // m_player.draw_collider(window);
    window.draw(m_player);
    window.draw(m_level_sprite);
}

void GameScreen::update(sf::RenderWindow& window, float elapsed) {
    m_level_manager.update(m_player, elapsed);
    // Log::log(Log::INFO, "UPDATE GAME {} \n", 1.0 / elapsed);
    m_player.update(elapsed);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_player.move_left(elapsed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_player.move_right(elapsed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_player.shoot();
    }
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE GAME\n");
}

GameScreen::GameScreen() {
    m_level_manager.load();

    m_player.set_texture("Resources/Space Shooter - 1/Ship/2.png");
    m_player.set_position(1920.f / 2, 1080.f - 80.f);

    m_background_texture.loadFromFile("Resources/Space Shooter - 1/Background/1.png");
    m_background_sprite.setTexture(m_background_texture);
    auto[tmpx, tmpy] = m_background_texture.getSize();
    m_background_sprite.setScale(1920.f / tmpx, 1080.f / tmpy);
}