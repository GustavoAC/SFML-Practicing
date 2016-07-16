/*!
   \file game.cpp
   \brief Game class implementation
*/

#include "game.hpp"

#include "configuration.hpp"
#include "player.hpp"
#include "meteor.hpp"
#include "random.hpp"
#include "saucer.hpp"

Game::Game(int x, int y) : _window(sf::VideoMode(x, y),"03_Asteroids"),
                           _world(x,y),
                           _nextSaucer(sf::seconds(random(10.f, 30.f))) {
    _window.setFramerateLimit(60);
    for(int i = 0; i < 4; ++i) {
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
        //std::cout << "FPS: " << 1.f/timeSinceLastUpdate.asSeconds() << "\n";

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
        } else {
            if (Configuration::player != nullptr)
                Configuration::player->processEvent(event);
        }
    }

    if (Configuration::player != nullptr)
        Configuration::player->processEvents();
}

void Game::update(sf::Time deltaTime) {

    _world.update(deltaTime);

    if (Configuration::isGameOver()) {
        _window.close();
    } else {
        if (Configuration::player == nullptr){
            Configuration::player = new Player(_world);
            Configuration::player->setPosition(_world.getX()/2,_world.getY()/2);
            _world.add(Configuration::player);
        }

        _nextSaucer -= deltaTime;

        if (_nextSaucer < sf::Time::Zero) {
            Saucer::newSaucer(_world);
            _nextSaucer = sf::seconds(random(10.f,30.f));
        }

        if (_world.size() <= 1) {
            initLevel();
        }
    }
}

void Game::initLevel() {
    Configuration::player->goToHyperspace();
    Configuration::player->setPosition(_world.getX()/2, _world.getY()/2);

    for (int i = 0; i < 4; ++i) {
        Meteor* meteor = new BigMeteor(_world);
        do{
            meteor->setPosition(random(0.f,(float)_world.getX()),random(0.f,(float)_world.getY()));
        }while(_world.isCollide(*meteor));
        _world.add(meteor);
    }
}

void Game::render() {
    _window.clear();
    _window.draw(_world);
    Configuration::draw(_window);
    _window.display();
}
