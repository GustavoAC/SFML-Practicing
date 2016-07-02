/*!
   \file game.cpp
   \brief Game class implementation
*/

#include "game.hpp"

Game::Game() : _window(sf::VideoMode(800, 600),"SFML Test") {
    _window.setFramerateLimit(60);
}

void Game::run(int minimum_frame_per_seconds) {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time TimePerFrame = sf::seconds(1.f/minimum_frame_per_seconds);

    while (_window.isOpen()) {
        processEvents();
        timeSinceLastUpdate = clock.restart();
        std::cout << "FPS: " << 1.f/timeSinceLastUpdate.asSeconds() << "\n";

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }

        update(timeSinceLastUpdate);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while(_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) //Close window
            _window.close();
        else if (event.type == sf::Event::KeyPressed) { //keyboard input
            if (event.key.code == sf::Keyboard::Escape)
                _window.close();
        }
    }
    _player.processEvents();
}

void Game::update(sf::Time deltaTime) {
    _player.update(deltaTime);
}

void Game::render() {
    _window.clear();
    _window.draw(_player);
    _window.display();
}
