#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "board.hpp"
#include "stats.hpp"
#include "piece.hpp"

class Game {
  public:
    Game(); //< constructor
    void run(int minimum_frame_per_seconds);

  private:
    void processEvents();//< Process events
    void update(sf::Time deltaTime); //< do some updates
    void render();//< draw all the stuff
    void newPiece();

    sf::RenderWindow _window; //< the window used to display the game
    std::unique_ptr<Piece> _currentPiece; //< the current piece
    Board _board; //< the game board
    Stats _stats; //< stats printer
    sf::Time _nextFall;
};

#endif
