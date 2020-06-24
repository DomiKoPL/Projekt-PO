#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"
#include "../gui/TextGenerator.hpp"
#include "../Log.hpp"
#include "../TextureManager.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(m_background_sprite);
    
    m_level_manager.draw(window);
    // Log::log(Log::INFO, "DRAW GAME\n");
    // m_player.draw_collider(window);
    window.draw(m_player);
    window.draw(m_level_sprite);

    // HUD

    int player_life = m_player.get_life();
    for(int i = 0; i < player_life; i++) {
        m_player_life_sprite.setPosition(20 + i * 40, 40);
        window.draw(m_player_life_sprite);
    }
}

void GameScreen::update(sf::RenderWindow& window, float elapsed) {
    m_background_current_y += m_background_move_speed * elapsed;
    auto[w, h] = m_background_texture.getSize();
    m_background_sprite.setTextureRect(sf::IntRect(0, (int)m_background_current_y, w, h));

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
    

    if(m_player.is_dead()) {
        Log::log(Log::INFO, "DEAD :(((\n");
    }
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE GAME\n");
}

GameScreen::GameScreen() {
    m_level_manager.load();

    m_player.set_texture("Resources/Space Shooter - 1/Ship/2.png");
    m_player.set_position(1920.f / 2, 1080.f - 40.f);

    m_background_texture.loadFromFile("Resources/Background/2.png");
    m_background_texture.setRepeated(true);
    // m_background_texture.loadFromFile("Resources/Space Shooter - 1/Background/1.png");
    m_background_sprite.setTexture(m_background_texture);
    auto[tmpx, tmpy] = m_background_texture.getSize();
    m_background_sprite.setScale(1920.f / tmpx, 1080.f / tmpy);

    m_player_life_sprite.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/HUD/LifeIcon.png"));
    auto[w, h] = TextureManager::instance().get_texture("Resources/Space Shooter - 1/HUD/LifeIcon.png").getSize();
    m_player_life_sprite.setScale(40.f / w, 40.f / w);
}