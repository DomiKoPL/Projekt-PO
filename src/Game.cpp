#include "Game.hpp"

void Game::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        for(sf::Event event; window.pollEvent(event); ) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        auto time_diff = clock.restart().asSeconds();

        // update

        window.clear(sf::Color::Black);

        // draw

        window.display();
    }
}

Game::Game() {
    window.create(sf::VideoMode(720, 480), "Floating Gra", sf::Style::None | sf::Style::Close);
    window.setFramerateLimit(60);
}

Game::~Game() {

}