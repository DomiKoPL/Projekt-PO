#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"
#include "../gui/TextGenerator.hpp"
#include "../Log.hpp"
#include "../TextureManager.hpp"
#include "../gui/TextGenerator.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(m_background_sprite);
    
    m_level_manager.draw(window);
    // Log::log(Log::INFO, "DRAW GAME\n");
    // m_player.draw_collider(window);
    if(m_player.is_dead()) {
        window.draw(m_game_over);
        if(m_time_from_death >= 2.f) {
            window.draw(m_press_space);
        }
    } 
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

    // Log::log(Log::INFO, "UPDATE GAME {} \n", 1.0 / elapsed);

    if(m_player.is_dead()) {
        m_level_manager.update(m_player, elapsed);
        m_player.update(elapsed);
        m_time_from_death += elapsed;


        if(m_time_from_death > 2.0f and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/4.ogg");
            ScreenManager::set_screen("MainMenuScreen");
        }
    } else {
        m_level_manager.update(m_player, elapsed);
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
            MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/1.ogg");
            MusicManager::instance().play_music("Resources/Space Shooter - 1/Music/4.ogg");
        }
    }
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE GAME\n");

    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/1.ogg");
            MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/4.ogg");
            ScreenManager::set_screen("MainMenuScreen");
        }
    }
}

void GameScreen::reset() {
    MusicManager::instance().play_music("Resources/Space Shooter - 1/Music/1.ogg");
    m_time_from_death = 0;

    m_level_manager = LevelManager();
    m_level_manager.load();


    m_player = Player();
    m_background_current_y = 0.f;

    m_player.set_texture("Resources/Space Shooter - 1/Ship/2.png");
    m_player.set_position(1920.f / 2, 1080.f - 40.f);

    m_background_texture.loadFromFile("Resources/Background/2.png");
    m_background_texture.setRepeated(true);

    m_background_sprite.setTexture(m_background_texture);
    auto[tmpx, tmpy] = m_background_texture.getSize();
    m_background_sprite.setScale(1920.f / tmpx, 1080.f / tmpy);

    m_player_life_sprite.setTexture(TextureManager::instance().get_texture("Resources/Space Shooter - 1/HUD/LifeIcon.png"));
    auto[w, h] = TextureManager::instance().get_texture("Resources/Space Shooter - 1/HUD/LifeIcon.png").getSize();
    m_player_life_sprite.setScale(40.f / w, 40.f / w);

    {
        m_game_over.setTexture(TextureManager::instance().get_texture("Resources/PNG/Text/game over.png"));
        auto[w, h] = TextureManager::instance().get_texture("Resources/PNG/Text/game over.png").getSize();
        m_game_over.setScale(700.f / w, 700.f / w);
        m_game_over.setOrigin(w / 2, h / 2);
        m_game_over.setPosition(1920 / 2, 1080 / 2);

        std::string text = "PRESS SPACE";
        m_press_space_texture = TextGenerator::get_text_texture(text, text.size() * 37);
        m_press_space.setTexture(m_press_space_texture);
        auto [x, y] = m_press_space_texture.getSize();
        m_press_space.setOrigin(x / 2, 0);
        m_press_space.setPosition(1920.f / 2, 1080 / 2 + 140);
    }
}

GameScreen::GameScreen() {
    m_level_manager = LevelManager();
    m_level_manager.load();

    m_time_from_death = 0;

    m_player = Player();
    m_background_current_y = 0.f;

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

    {
        m_game_over.setTexture(TextureManager::instance().get_texture("Resources/PNG/Text/game over.png"));
        auto[w, h] = TextureManager::instance().get_texture("Resources/PNG/Text/game over.png").getSize();
        m_game_over.setScale(700.f / w, 700.f / w);
        m_game_over.setOrigin(w / 2, h / 2);
        m_game_over.setPosition(1920 / 2, 1080 / 2);

        std::string text = "PRESS SPACE";
        m_press_space_texture = TextGenerator::get_text_texture(text, text.size() * 37);
        m_press_space.setTexture(m_press_space_texture);
        auto [x, y] = m_press_space_texture.getSize();
        m_press_space.setOrigin(x / 2, 0);
        m_press_space.setPosition(1920.f / 2, 1080 / 2 + 140);
    }
}