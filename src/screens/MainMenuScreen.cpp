#include "MainMenuScreen.hpp"
#include "ScreenManager.hpp"
#include "../Log.hpp"
#include "../Settings.hpp"

void MainMenuScreen::draw(sf::RenderWindow& window) {
    // Log::log(Log::INFO, "DRAW MainMenu\n");
    for(auto& button : m_buttons) {
        window.draw(button.get());
    }
}

void MainMenuScreen::update(sf::RenderWindow& window, float elapsed) {
    // Log::log(Log::INFO, "UPDATE MainMenu\n");
    for(auto& button : m_buttons) {
        button.get().update(window);
    }
}

void MainMenuScreen::handle_event(sf::RenderWindow& window, sf::Event event) {
    for(auto& button : m_buttons) {
        button.get().update(window, event);
    }

    // Log::log(Log::INFO, "HANDLE MainMenu\n");
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Escape) {
            // to jest nic ciekawego
        }
    }
}

MainMenuScreen::MainMenuScreen() {
    play_button.add_function_when_clicked([&]() {
        Log::log(Log::INFO, "Button clicked\n");
        ScreenManager::set_screen("GameScreen");
    });
    play_button.load_texture("Resources/PNG/Menu/Level menu/play.png");
    play_button.load_highlight_texture("Resources/PNG/Menu/Level menu/play_locked.png");
    play_button.setPosition(1920.f / 2, 400.f);
    play_button.set_size(500, 160);
    m_buttons.push_back(play_button);

    exit_button.add_function_when_clicked([&]() {
        Log::log(Log::INFO, "Button clicked\n");
        ScreenManager::close();
    });
    exit_button.load_texture("Resources/PNG/Menu/Pause menu/exit.png");
    exit_button.load_highlight_texture("Resources/PNG/Menu/Pause menu/exit_locked.png");

    exit_button.setPosition(1920.f / 2.f, 600.f);
    exit_button.set_size(500, 160);
    m_buttons.push_back(exit_button);
}

MainMenuScreen::~MainMenuScreen() {

}