#include "GameScreen.hpp"
#include <iostream>
#include "ScreenManager.hpp"
#include "../gui/TextGenerator.hpp"
#include "../Log.hpp"
#include "../TextureManager.hpp"
#include "../gui/TextGenerator.hpp"
#include "../Settings.hpp"

void GameScreen::draw(sf::RenderWindow& window) {
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

    // sf::RectangleShape left_bar;
    // left_bar.setFillColor(sf::Color::Black);
    // left_bar.setSize({150, 1080});
    // window.draw(left_bar);

    int player_life = m_player.get_life();
    for(int i = 0; i < player_life; i++) {
        m_player_life_sprite.setPosition(20 + i * 40, 40);
        window.draw(m_player_life_sprite);
    }
    
    // sf::RectangleShape shape;
    // shape.setPosition(20, 90);
    // float minspeed = Settings::get<float>("player", "move_speed", "min"), maxspeed = Settings::get<float>("player", "move_speed", "max");
    // float p = (m_player.get_move_speed() - minspeed) / (maxspeed - minspeed);
    // shape.setSize({5 + p * 120, 20.f});
    // shape.setFillColor(sf::Color::Red);

    // sf::RectangleShape shapefreq;
    // shapefreq.setPosition(20, 110);
    // float minfreq = Settings::get<float>("player", "shoot_frequency", "min"), maxfreq = Settings::get<float>("player", "shoot_frequency", "max");
    // float pfreq = (maxfreq - m_player.get_shoot_frequency()) / (maxfreq - minfreq);
    // shapefreq.setSize({5 + pfreq * 120, 20.f});
    // shapefreq.setFillColor(sf::Color::Blue);

    // window.draw(shape);
    // window.draw(shapefreq);

    if(m_pause) {
        window.draw(m_menu);
        window.draw(m_resume);

        window.draw(m_pause_sprite);
    }
}

void GameScreen::update(sf::RenderWindow& window, float elapsed) {
    // Log::log(Log::INFO, "UPDATE GAME {} \n", 1.0 / elapsed);

    if(not m_pause) {
        if(m_player.is_dead()) {
            m_level_manager.update(m_player, elapsed);
            m_player.update(elapsed);
            m_time_from_death += elapsed;


            if(m_time_from_death > 2.0f and sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/4.ogg");
                MusicManager::instance().play_music("Resources/Space Shooter - 1/Music/3.ogg");
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
    } else {
        m_menu.update(window);
        m_resume.update(window);
    }
}

void GameScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE GAME\n");

    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            m_level_manager.flip_pause();
            m_pause = not m_pause;
        }
    }

    if(m_pause) {
        m_menu.update(window, event);
        m_resume.update(window, event);
    }
}

void GameScreen::reset() {
    m_pause = false;
    MusicManager::instance().play_music("Resources/Space Shooter - 1/Music/1.ogg");
    m_time_from_death = 0;

    m_level_manager = LevelManager();
    m_level_manager.load();

    m_player = Player();

    m_player.set_texture("Resources/Space Shooter - 1/Ship/2.png");
    m_player.set_position(1920.f / 2, 1080.f - 40.f);

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
    m_pause = false;
    m_level_manager = LevelManager();
    m_level_manager.load();

    m_time_from_death = 0;

    m_player = Player();

    m_player.set_texture("Resources/Space Shooter - 1/Ship/2.png");
    m_player.set_position(1920.f / 2, 1080.f - 40.f);

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

    m_menu.load_texture("Resources/PNG/Buttons/home.png");
    m_menu.load_highlight_texture("Resources/PNG/Buttons/home_locked.png");
    m_menu.set_width(100);
    m_menu.setPosition(1920.f / 2 - 80.f, 1080.f / 2);
    m_menu.add_function_when_clicked([&]() {
        MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/4.ogg");
        MusicManager::instance().play_music("Resources/Space Shooter - 1/Music/3.ogg");
        ScreenManager::set_screen("MainMenuScreen");
    });

    m_resume.load_texture("Resources/PNG/Buttons/play.png");
    m_resume.load_highlight_texture("Resources/PNG/Buttons/play_locked.png");
    m_resume.set_width(100);
    m_resume.setPosition(1920.f / 2 + 80.f, 1080.f / 2);
    m_resume.add_function_when_clicked([&]() {
        m_level_manager.flip_pause();
        m_pause = not m_pause;
    });

    {
        TextureManager::instance().add_texture("pause", TextGenerator::get_text_texture("PAUSE", 37 * 4 * 5));
        m_pause_sprite.setTexture(TextureManager::instance().get_texture("pause"));
        auto[w, h] = TextureManager::instance().get_texture("pause").getSize();
        m_pause_sprite.setOrigin(w / 2, h / 2);
        m_pause_sprite.setPosition(1920.f / 2, 500.f);
    }
}