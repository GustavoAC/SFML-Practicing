#include "game.hpp"
#include <iostream>

void rand_init() {
    srand(time(0));
}

float random(const float &min, const float &max) {
    return (rand()/float(RAND_MAX))*(max-min) + min;
}

int random(const int &min, const int &max) {
    return rand()%(max-min+1) + min;
}

Game::Game() : _window(sf::VideoMode(800, 600),"SFML Tetris"), _board() {
    _window.setFramerateLimit(60);
    // std::cout << "ka" << "\n";
    rand_init();
    // std::cout << "ki" << "\n";
    _board.setPosition(10,10);
    // std::cout << "ku" << "\n";
    _stats.setPosition(300,10);
    // std::cout << "ke" << "\n";
    newPiece();
    // std::cout << "ko" << "\n";
}

void Game::run(int minimum_frame_per_seconds) {
    // std::cout << "ha" << "\n";
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time TimePerFrame = sf::seconds(1.f/minimum_frame_per_seconds);

    // std::cout << "he" << "\n";
    while (_window.isOpen()) {
        processEvents();
        timeSinceLastUpdate = clock.restart();
        // std::cout << "hi" << "\n";
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        // std::cout << "ho" << "\n";
        update(timeSinceLastUpdate);
        render();
        // std::cout << "hu" << "\n";
    }
}

void Game::processEvents() {
    sf::Event event;
    while(_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)//Close window
            _window.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                _window.close();
            } else if (event.key.code == sf::Keyboard::Down) {
                _board.move(*_currentPiece, 0, 1);
            } else if (event.key.code == sf::Keyboard::Up) {
                _board.move(*_currentPiece, 0, -1);
            } else if (event.key.code == sf::Keyboard::Left) {
                _board.move(*_currentPiece, -1, 0);
            } else if (event.key.code == sf::Keyboard::Right) {
                _board.move(*_currentPiece, 1, 0);
            } else if (event.key.code == sf::Keyboard::Space) {
                _board.drop(*_currentPiece);
                newPiece();
            } else if (event.key.code == sf::Keyboard::S) {
                _board.rotateRight(*_currentPiece);
            } else if (event.key.code == sf::Keyboard::D) {
                _board.rotateLeft(*_currentPiece);
            }
        }
    }
}

void Game::update(sf::Time deltaTime) {
    if(not _board.isGameOver()) {
        _stats.addLines(_board.clearLines(*_currentPiece));
        _nextFall += deltaTime;
        if((not _board.isFallen(*_currentPiece)) and
            (_currentPiece->getTimeSinceLastMove() > sf::seconds(1.f)))
                newPiece();

        sf::Time max_time = sf::seconds(std::max(0.1, 0.6-0.005*_stats.getLvl()));
        while(_nextFall > max_time) {
            _nextFall -= max_time;
            _board.move(*_currentPiece, 0, 1);
        }
    } else {
        _stats.gameOver();
    }
}

void Game::render() {
    _window.clear();
    if(not _board.isGameOver())
        _window.draw(_board);
    _window.draw(_stats);
    _window.display();
}

void Game::newPiece() {
    _currentPiece.reset(new Piece((Piece::TetriminoTypes) random(0,Piece::TetriminoTypes::SIZE-1),0));
    // std::cout << "1" << "\n";
    _board.spawn(*_currentPiece);
    // std::cout << "2" << "\n";
}
