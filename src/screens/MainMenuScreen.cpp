#include "MainMenuScreen.hpp"
#include "ScreenManager.hpp"
#include "../Log.hpp"
#include "../Settings.hpp"
#include "../MusicManager.hpp"
#include "../gui/TextGenerator.hpp"

void MainMenuScreen::draw(sf::RenderWindow& window) {
    // Log::log(Log::INFO, "DRAW MainMenu\n");
    window.draw(m_background_sprite);

    m_level_manager.draw(window);
    
    window.draw(m_name);
    
    for(auto& button : m_buttons) {
        window.draw(button.get());
    }
}

void MainMenuScreen::update(sf::RenderWindow& window, float elapsed) {
    // Log::log(Log::INFO, "UPDATE MainMenu\n");
    m_background_current_y += m_background_move_speed * elapsed;
    auto[w, h] = m_background_texture.getSize();
    m_background_sprite.setTextureRect(sf::IntRect(0, (int)m_background_current_y, w, h));
    
    m_level_manager.update_demo(elapsed);

    for(auto& button : m_buttons) {
        button.get().update(window);
    }
}

void MainMenuScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE MainMenu\n");
    for(auto& button : m_buttons) {
        button.get().update(window, event);
    }

    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Space) {
            MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/3.ogg");
            ScreenManager::set_screen("GameScreen");
        }
    }
}

MainMenuScreen::MainMenuScreen() {
    play_button.add_function_when_clicked([&]() {
        // Log::log(Log::INFO, "Button clicked\n");
        MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/3.ogg");
        ScreenManager::set_screen("GameScreen");
    });
    play_button.load_texture("Resources/PNG/Menu/Level menu/play.png");
    play_button.load_highlight_texture("Resources/PNG/Menu/Level menu/play_locked.png");
    play_button.setPosition(1920.f / 2, 400.f);
    play_button.set_size(500, 160);
    m_buttons.push_back(play_button);

    options_button.add_function_when_clicked([&]() {
        // Log::log(Log::INFO, "Button clicked\n");
        ScreenManager::set_screen("OptionsScreen");
    });
    options_button.load_texture("Resources/PNG/Menu/Pause menu/options.png");
    options_button.load_highlight_texture("Resources/PNG/Menu/Pause menu/options_locked.png");

    options_button.setPosition(1920.f / 2.f, 600.f);
    options_button.set_size(500, 160);
    m_buttons.push_back(options_button);

    exit_button.add_function_when_clicked([&]() {
        // Log::log(Log::INFO, "Button clicked\n");
        MusicManager::instance().stop_music("Resources/Space Shooter - 1/Music/3.ogg");
        ScreenManager::close();
    });
    exit_button.load_texture("Resources/PNG/Menu/Pause menu/exit.png");
    exit_button.load_highlight_texture("Resources/PNG/Menu/Pause menu/exit_locked.png");

    exit_button.setPosition(1920.f / 2.f, 800.f);
    exit_button.set_size(500, 160);
    m_buttons.push_back(exit_button);

    m_background_texture.loadFromFile("Resources/Background/2.png");
    m_background_texture.setRepeated(true);

    m_background_sprite.setTexture(m_background_texture);
    auto[tmpx, tmpy] = m_background_texture.getSize();
    m_background_sprite.setScale(1920.f / tmpx, 1080.f / tmpy);

    {
        m_name_texture = TextGenerator::get_text_texture("SPACE WAR", 37 * 9 * 6);
        auto[x, y] = m_name_texture.getSize();
        m_name.setTexture(m_name_texture);
        m_name.setOrigin(x / 2, 0);
        m_name.setPosition(1920 / 2, 50);
    }
}

void MainMenuScreen::reset() {
    MusicManager::instance().play_music("Resources/Space Shooter - 1/Music/3.ogg");
    m_background_current_y = 0;
    m_level_manager = LevelManager(true);
    m_level_manager.load();
}

MainMenuScreen::~MainMenuScreen() {

}