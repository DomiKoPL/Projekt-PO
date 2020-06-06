#include "Game.hpp"
#include "screens/ScreenManager.hpp"
#include "Settings.hpp"

void Game::run() {
	sf::Clock clock;
	while(window.isOpen()) {
		for(sf::Event event; window.pollEvent(event); ) {
			ScreenManager::handle_event(window, event);
			if(event.type == sf::Event::Closed) {
				window.close();
			}
		}

		auto time_diff = clock.restart().asSeconds();
		ScreenManager::update(window, time_diff);

		window.clear(sf::Color::Black);

		ScreenManager::draw(window);

		window.display();
	}
}

Game::Game() {
	// Settings::get<unsigned int>("width");
	// Settings::get<int>("highscore");

	window.create(sf::VideoMode(720, 480), "Floating Gra", sf::Style::None | sf::Style::Close);
	window.setFramerateLimit(60);
	ScreenManager::setup();
}

Game::~Game() {
	
}