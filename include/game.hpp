/*!
   \file game.hpp
   \brief Game class function signatures
*/

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"
#include "player.hpp"

class Game {
  public:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(int x=800, int y=600);
    void run(int minimum_frame_per_seconds);

  private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    sf::RenderWindow _window;
    World _world;
};

#endif
