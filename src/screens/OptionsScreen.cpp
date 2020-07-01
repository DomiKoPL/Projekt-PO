#include "OptionsScreen.hpp"
#include "ScreenManager.hpp"
#include "../Log.hpp"
#include "../Settings.hpp"
#include "../MusicManager.hpp"
#include "../TextureManager.hpp"

void OptionsScreen::draw(sf::RenderWindow& window) {
    // Log::log(Log::INFO, "DRAW Options\n");
    m_level_manager.draw(window);

    for(auto& button : m_buttons) {
        window.draw(button.get());
    }
    
    window.draw(m_master_volume);
    window.draw(m_music_volume);
    window.draw(m_sound_volume);

    for(auto& bar : m_bars) {
        window.draw(bar.get());
    }
}

void OptionsScreen::update(sf::RenderWindow& window, float elapsed) {
    // Log::log(Log::INFO, "UPDATE Options\n");
    m_level_manager.update_demo(elapsed);

    for(auto& button : m_buttons) {
        button.get().update(window);
    }

    m_master_bar.update(MusicManager::instance().get_master_volume());
    m_music_bar.update(MusicManager::instance().get_music_volume());
    m_sound_bar.update(MusicManager::instance().get_sound_volume());
}

void OptionsScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    // Log::log(Log::INFO, "HANDLE Options\n");
    for(auto& button : m_buttons) {
        button.get().update(window, event);
    }
}

void OptionsScreen::reset() {
    m_level_manager = LevelManager(true);
    m_level_manager.load();
}

OptionsScreen::OptionsScreen() {
    {
        TextureManager::instance().add_texture("master_volume", TextGenerator::get_text_texture("master volume", 37 * 13));
        m_master_volume.setTexture(TextureManager::instance().get_texture("master_volume"));
        auto[x, y] = TextureManager::instance().get_texture("master_volume").getSize();
        m_master_volume.setOrigin(x / 2, 0);
        m_master_volume.setPosition(1920.f / 2, 330);
    }
    
    m_master_volume_add.add_function_when_clicked([&]() {
        MusicManager::instance().change_master_volume(5);
    });
    m_master_volume_add.load_texture("Resources/PNG/Buttons/plus.png");
    m_master_volume_add.load_highlight_texture("Resources/PNG/Buttons/plus_locked.png");
    m_master_volume_add.setPosition(1920.f / 2 + 300, 400.f);
    m_master_volume_add.set_width(50);
    m_buttons.push_back(m_master_volume_add);

    m_master_volume_substract.add_function_when_clicked([&]() {
        MusicManager::instance().change_master_volume(-5);
    });
    m_master_volume_substract.load_texture("Resources/PNG/Buttons/separate.png");
    m_master_volume_substract.load_highlight_texture("Resources/PNG/Buttons/separate_locked.png");
    m_master_volume_substract.setPosition(1920.f / 2 - 300, 400.f);
    m_master_volume_substract.set_width(50);
    m_buttons.push_back(m_master_volume_substract);

    m_master_bar = ProgressBar(0, 100);
    m_master_bar.setPosition(1920.f / 2, 400);
    m_master_bar.set_size(550, 50);
    m_bars.push_back(m_master_bar);

    {
        TextureManager::instance().add_texture("music_volume", TextGenerator::get_text_texture("music volume", 37 * 12));
        m_music_volume.setTexture(TextureManager::instance().get_texture("music_volume"));
        auto[x, y] = TextureManager::instance().get_texture("music_volume").getSize();
        m_music_volume.setOrigin(x / 2, 0);
        m_music_volume.setPosition(1920.f / 2, 450);
    }

    m_music_volume_add.add_function_when_clicked([&]() {
        MusicManager::instance().change_music_volume(5);
    });
    m_music_volume_add.load_texture("Resources/PNG/Buttons/plus.png");
    m_music_volume_add.load_highlight_texture("Resources/PNG/Buttons/plus_locked.png");
    m_music_volume_add.setPosition(1920.f / 2 + 300, 520.f);
    m_music_volume_add.set_width(50);
    m_buttons.push_back(m_music_volume_add);

    m_music_volume_substract.add_function_when_clicked([&]() {
        MusicManager::instance().change_music_volume(-5);
    });
    m_music_volume_substract.load_texture("Resources/PNG/Buttons/separate.png");
    m_music_volume_substract.load_highlight_texture("Resources/PNG/Buttons/separate_locked.png");
    m_music_volume_substract.setPosition(1920.f / 2 - 300, 520.f);
    m_music_volume_substract.set_width(50);
    m_buttons.push_back(m_music_volume_substract);

    m_music_bar = ProgressBar(0, 100);
    m_music_bar.setPosition(1920.f / 2, 520.f);
    m_music_bar.set_size(550, 50);
    m_bars.push_back(m_music_bar);

    {
        TextureManager::instance().add_texture("sound_volume", TextGenerator::get_text_texture("sound volume", 37 * 12));
        m_sound_volume.setTexture(TextureManager::instance().get_texture("sound_volume"));
        auto[x, y] = TextureManager::instance().get_texture("sound_volume").getSize();
        m_sound_volume.setOrigin(x / 2, 0);
        m_sound_volume.setPosition(1920.f / 2, 570);
    }

    m_sound_volume_add.add_function_when_clicked([&]() {
        MusicManager::instance().change_sound_volume(5);
    });
    m_sound_volume_add.load_texture("Resources/PNG/Buttons/plus.png");
    m_sound_volume_add.load_highlight_texture("Resources/PNG/Buttons/plus_locked.png");
    m_sound_volume_add.setPosition(1920.f / 2 + 300, 640.f);
    m_sound_volume_add.set_width(50);
    m_buttons.push_back(m_sound_volume_add);

    m_sound_volume_substract.add_function_when_clicked([&]() {
        MusicManager::instance().change_sound_volume(-5);
    });
    m_sound_volume_substract.load_texture("Resources/PNG/Buttons/separate.png");
    m_sound_volume_substract.load_highlight_texture("Resources/PNG/Buttons/separate_locked.png");
    m_sound_volume_substract.setPosition(1920.f / 2 - 300, 640.f);
    m_sound_volume_substract.set_width(50);
    m_buttons.push_back(m_sound_volume_substract);

    m_sound_bar = ProgressBar(0, 100);
    m_sound_bar.setPosition(1920.f / 2, 640);
    m_sound_bar.set_size(550, 50);
    m_bars.push_back(m_sound_bar);

    m_menu.add_function_when_clicked([&]() {
        ScreenManager::set_screen("MainMenuScreen");
    });
    m_menu.load_texture("Resources/PNG/Buttons/home.png");
    m_menu.load_highlight_texture("Resources/PNG/Buttons/home_locked.png");
    m_menu.setPosition(1920 / 2, 200.f);
    m_menu.set_width(100);
    m_buttons.push_back(m_menu);
}

OptionsScreen::~OptionsScreen() {

}