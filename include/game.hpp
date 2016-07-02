/*!
   \file game.hpp
   \brief Game class function signatures
*/

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "configuration.hpp"
#include "player.hpp"

class Game {
  public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game();
    void run(int minimum_frame_per_seconds);

  private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    sf::RenderWindow _window;
    Player _player;
};

#endif
