#include <cassert>
#include "piece.hpp"

const sf::Color Piece::TetriminoColors[Piece::TetriminoTypes::SIZE]= {
    sf::Color::Blue,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Cyan,
    sf::Color::Magenta,
    sf::Color::White,
    sf::Color(195,132,58)
};

const char Piece::TetriminoPieces[Piece::TetriminoTypes::SIZE][Piece::NB_ROTATIONS]
                                  [Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {
    { // O
        {
            {0,0,0,0},
            {0,1,2,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,2,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,2,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,2,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    },
    {//I
        {
            {0,0,0,0},
            {1,1,2,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,0},
            {0,0,1,0},
            {0,0,1,0}
        },
        {
            {0,0,0,0},
            {1,1,2,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,0},
            {0,0,1,0},
            {0,0,1,0}
        }
    },
    {//S
        {
            {0,0,0,0},
            {0,0,2,1},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,1},
            {0,0,0,1},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,0,2,1},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,1},
            {0,0,0,1},
            {0,0,0,0}
        }
    },
    {//Z
        {
            {0,0,0,0},
            {0,1,2,0},
            {0,0,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,1},
            {0,0,2,1},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,2,0},
            {0,0,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,1},
            {0,0,2,1},
            {0,0,1,0},
            {0,0,0,0}
        }
    },
    {//L
        {
            {0,0,0,0},
            {0,1,2,1},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,0},
            {0,0,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,1},
            {0,1,2,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,0,2,0},
            {0,0,1,0},
            {0,0,0,0}
        }
    },
    {//J
        {
            {0,0,0,0},
            {0,1,2,1},
            {0,0,0,1},
            {0,0,0,0}
        },
        {
            {0,0,1,1},
            {0,0,2,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,2,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    },
    {//T
        {
            {0,0,0,0},
            {0,1,2,1},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,0,2,1},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,1,2,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {0,1,2,0},
            {0,0,1,0},
            {0,0,0,0}
        }
    }
};

Piece::Piece(TetriminoTypes type, short int rotation) :
             _type(type), _rotation(rotation), _positionX(0), _positionY(0) {
    assert(rotation >= 0 and rotation < NB_ROTATIONS);
}

Piece::TetriminoTypes Piece::getType() const {
    return _type;
}

short int Piece::getRotation() const {
    return _rotation;
}

int Piece::getPosX() const {
    return _positionX;
}

int Piece::getPosY() const {
    return _positionY;
}

sf::Time Piece::getTimeSinceLastMove() const {
    return _clockSinceLastMove.getElapsedTime();
}

void Piece::setRotation(short int rotation) {
    assert(rotation >= 0 and rotation < NB_ROTATIONS);
    _rotation = rotation;
    _clockSinceLastMove.restart();
}

void Piece::setPosition(int x, int y) {
    _positionX = x;
    _positionY = y;
    _clockSinceLastMove.restart();
}
