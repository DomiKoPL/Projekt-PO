#include "Game.hpp"
#include "screens/ScreenManager.hpp"
#include "Settings.hpp"
#include "Log.hpp"

void Game::run() {
	sf::Clock clock;
	while(window.isOpen()) {
		for(sf::Event event; window.pollEvent(event); ) {
			ScreenManager::handle_event(window, event);
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		auto elapsed = clock.restart().asSeconds();
		ScreenManager::update(window, elapsed);

		window.clear(sf::Color::Black);

		ScreenManager::draw(window);

		window.display();
	}
}

Game::Game() {
	Log::set_level(Log::INFO);
	Settings::load();

	window.create(sf::VideoMode(Settings::get<unsigned int>("width"), Settings::get<unsigned int>("height")), "Floating Gra", sf::Style::None | sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(Settings::get<unsigned int>("framerate"));
	ScreenManager::setup();
}

Game::~Game() {
	Settings::save();
	ScreenManager::clear();
}