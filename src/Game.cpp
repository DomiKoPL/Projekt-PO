#include "Game.hpp"
#include "screens/ScreenManager.hpp"
#include "Settings.hpp"
#include "Log.hpp"
#include "Weapon.hpp"
#include "gui/TextGenerator.hpp"

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

	window.create(sf::VideoMode(Settings::get<unsigned int>("width"), Settings::get<unsigned int>("height")), "SPACE WAR", sf::Style::Fullscreen);

	//* dzieki View wszedzie zakladamy ze nasze okno ma rozmiar 1920x1080
	//* uzywamy funkcji window.mapPixelToCoords(point) do zamiany wspolrzednych
	window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
	sf::Mouse::setPosition(sf::Vector2i(Settings::get<unsigned int>("width") / 2, Settings::get<unsigned int>("height") / 2), window);
	window.setFramerateLimit(Settings::get<unsigned int>("framerate"));
	Weapons::load();
	ScreenManager::setup();
}

Game::~Game() {
	Settings::save();
	ScreenManager::clear();
}