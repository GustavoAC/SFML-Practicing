/*!
   \file game.cpp
   \brief Game class implementation
*/

#include "game.hpp"

#include "configuration.hpp"
#include "player.hpp"
#include "meteor.hpp"
#include "random.hpp"

Game::Game(int x, int y) : _window(sf::VideoMode(x, y),"03_Asteroids"), _world(x,y) {
    _window.setFramerateLimit(60);
    for(int i = 0; i < 3;++i) {
        Meteor* meteor = new BigMeteor(_world);
        meteor->setPosition(random(0.f,(float)_world.getX()),random(0.f,(float)_world.getY()));
        _world.add(meteor);
    }
    Configuration::player = new Player(_world);
    Configuration::player->setPosition(200,200);
    _world.add(Configuration::player);
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
        }else {
            Configuration::player->processEvent(event);
        }
    }
    Configuration::player->processEvents();
}

void Game::update(sf::Time deltaTime) {
    _world.update(deltaTime);
}

void Game::render() {
    _window.clear();
    _window.draw(_world);
    _window.display();
}
