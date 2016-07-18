#include <cassert>
#include <iostream>
#include "board.hpp"

constexpr int CELL_EMPTY = -1;

Board::Board(int columns, int lines, int cell_x, int cell_y):
            _columns(columns),
            _lines(lines),
            _cellX(cell_x),
            _cellY(cell_y),
            _isGameOver(false),
            _grid(sf::VertexArray(sf::Lines, (_lines+1+_columns+1)*2)),
            _gridContent(new int[_lines*_columns]) {
    std::memset(_gridContent, CELL_EMPTY, _lines*_columns*sizeof(int));
    sf::Color gridColor(55,55,55);
    _grid = sf::VertexArray(sf::Lines, (_lines+1+_columns+1)*2);
    for(int i=0; i<=_lines; ++i) {
        _grid[i*2] = sf::Vertex(sf::Vector2f(0,i*_cellY));
        _grid[i*2+1] = sf::Vertex(sf::Vector2f(_columns*_cellX, i*_cellY));
        _grid[i*2].color = gridColor;
        _grid[i*2+1].color = gridColor;
    }
    for(int i=0;i<=columns;++i) {
        _grid[(_lines+1)*2 + i*2] = sf::Vertex(sf::Vector2f(i*_cellX,0));
        _grid[(_lines+1)*2 + i*2+1] = sf::Vertex(sf::Vector2f(i*_cellX,_lines*_cellY));
        _grid[(_lines+1)*2 + i*2].color = gridColor;
        _grid[(_lines+1)*2 + i*2+1].color = gridColor;
    }
}

Board::~Board() {
    delete _gridContent;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    for(int y = 0; y < _lines; ++y)
        for(int x = 0; x < _columns; ++x) {
            if(_gridContent[y*_columns + x] != CELL_EMPTY) {
                sf::RectangleShape rectangle(sf::Vector2f(_cellX, _cellY));
                rectangle.setFillColor(Piece::TetriminoColors[_gridContent[y*_columns + x]]);
                rectangle.setPosition(x*_cellX, y*_cellY);
                target.draw(rectangle, states);
            }
        }
    target.draw(_grid, states);
}

void Board::spawn(Piece& piece) {
    piece.setPosition(_columns/2, 0);
    // std::cout << "1.1" << "\n";
    for(int x = 0; x < _columns; ++x) {
        // std::cout << "1.2" << "\n";
        if(_gridContent[x] != CELL_EMPTY) {
            _isGameOver = true;
            break;
        }
        // std::cout << "1.3" << "\n";
    }
    draw(piece);
    // std::cout << "1.4" << "\n";
}

bool Board::move(Piece& piece, int delta_x, int delta_y) {
    delta_x += piece.getPosX();
    delta_y += piece.getPosY();
    clear(piece);
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    bool movable = true;
    flood(delta_x, delta_y, (int)Piece::PIVOT_X, (int)Piece::PIVOT_Y,
          piece.getType(), piece.getRotation(), visited, movable);
    if (movable)
        piece.setPosition(delta_x,delta_y);
    draw(piece);
    return movable;
}

bool Board::isFallen(const Piece& piece) {
    clear(piece);
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    bool fallen = true;
    flood(piece.getPosX(), piece.getPosY()+1, (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y, piece.getType(), piece.getRotation(), visited, fallen);
    draw(piece);

    return fallen;
}

void Board::drop(Piece& piece) {
    while(move(piece,0,1));
}

bool Board::rotateLeft(Piece& piece) {
    int rotation = piece.getRotation();
    if(rotation > 0)
        --rotation;
    else
        rotation = Piece::NB_ROTATIONS - 1;
    return rotate(piece,rotation);
}

bool Board::rotateRight(Piece& piece) {
    int rotation = piece.getRotation();
    if(rotation < Piece::NB_ROTATIONS -1)
        ++rotation;
    else
        rotation = 0;
    return rotate(piece, rotation);
}

bool Board::isGameOver(){
    return _isGameOver;
}

bool Board::rotate(Piece& piece, int rotation) {
    assert(rotation >= 0 and rotation < Piece::NB_ROTATIONS);
    clear(piece);
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    bool rotable = true;
    flood((int)piece.getPosX(), (int)piece.getPosY(), (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y, piece.getType(),rotation, visited, rotable);
    if(rotable)
        piece.setRotation(rotation);
    draw(piece);
    return rotable;
}

void Board::draw(const Piece& piece) {
    flood(piece, piece.getType());
}

void Board::clear(const Piece& piece) {
    flood(piece, CELL_EMPTY);
}

void Board::flood(const Piece& piece, int value) {
    // std::cout << "a1" << "\n";
    bool visited[Piece::MATRIX_SIZE][Piece::MATRIX_SIZE] = {{false}};
    // std::cout << "a2" << "\n";
    flood((int)piece.getPosX(), (int)piece.getPosY(), (int)Piece::PIVOT_X,
          (int)Piece::PIVOT_Y, piece.getType(), piece.getRotation(), visited, value);
    // std::cout << "a3" << "\n";
}

void Board::flood(int grid_x, int grid_y, int piece_x, int piece_y,
                  Piece::TetriminoTypes type, int rotation,
                  bool visited[][Piece::MATRIX_SIZE], int value) {
    // std::cout << "flood1" << "\n";
    if(piece_x < 0 or piece_x >= Piece::MATRIX_SIZE
       or piece_y < 0 or piece_y >= Piece::MATRIX_SIZE
       or grid_x < 0 or grid_x >= (int)_columns
       or grid_y < 0 or grid_y >= (int)_lines
       or visited[piece_y][piece_x] == true
       or Piece::TetriminoPieces[type][rotation][piece_y][piece_x] == 0)
        return;


    // std::cout << "flood2" << "\n";
    visited[piece_y][piece_x] = true;

    // std::cout << "flood3" << "\n";
    _gridContent[grid_y*_columns + grid_x] = value;

    // std::cout << "flood4" << "\n";
    flood(grid_x, grid_y-1, piece_x, piece_y-1, type, rotation, visited, value);
    flood(grid_x+1, grid_y, piece_x+1, piece_y, type, rotation, visited, value);
    flood(grid_x, grid_y+1, piece_x, piece_y+1, type, rotation, visited, value);
    flood(grid_x-1, grid_y, piece_x-1, piece_y, type, rotation, visited, value);

    // std::cout << "floodend" << "\n";
}

void Board::flood(int grid_x, int grid_y, int piece_x,int piece_y,
                  Piece::TetriminoTypes type, int rotation,
                  bool visited[][Piece::MATRIX_SIZE], bool& flag) {
    if (piece_x < 0 or piece_x >= Piece::MATRIX_SIZE or
        piece_y < 0 or piece_y >= Piece::MATRIX_SIZE or
        visited[piece_y][piece_x] == true or
        Piece::TetriminoPieces[type][rotation][piece_y][piece_x] == 0)
            return;

    visited[piece_y][piece_x] = true;

    if (grid_x < 0 or grid_x >= (int)_columns or
        grid_y < 0 or grid_y >= (int)_lines or
        _gridContent[grid_y*_columns + grid_x] != CELL_EMPTY) {
            flag = false;
            return;
    }

    flood(grid_x, grid_y-1, piece_x, piece_y-1, type, rotation, visited, flag);
    flood(grid_x+1, grid_y, piece_x+1, piece_y, type, rotation, visited, flag);
    flood(grid_x, grid_y+1, piece_x, piece_y+1, type, rotation, visited, flag);
    flood(grid_x-1, grid_y, piece_x-1, piece_y, type, rotation, visited, flag);
}

void Board::clearLine(int yy) {
    assert(yy < _lines);
    for(int y=yy; y > 0; --y)
        for(int x=0; x < _columns; ++x)
            _gridContent[y*_columns + x] = _gridContent[(y-1)*_columns + x];
}

int Board::clearLines(const Piece& piece) {
    int nb_delete = 0;
    clear(piece);
    for(int y = 0, x = 0; y < _lines; ++y) {
        x = 0;
        for( ;_gridContent[y*_columns + x] != CELL_EMPTY and x < _columns; ++x);
        if(x == _columns) {
            clearLine(y);
            ++nb_delete;
        }
    }
    draw(piece);
    return nb_delete;
}
