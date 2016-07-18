#include "stats.hpp"

constexpr int FONT_SIZE = 24;

Stats::Stats() : _nbRows(0), _nbScore(0), _nbLvl(0), _isGameOver(false) {
    _font.loadFromFile("media/font/OpenSans.ttf");
    _textRows.setFont(_font);
    _textRows.setString("rows : 0");
    _textRows.setCharacterSize(FONT_SIZE);
    _textRows.setPosition(0,0);

    _textScore.setFont(_font);
    _textScore.setString("score : 0");
    _textScore.setCharacterSize(FONT_SIZE);
    _textScore.setPosition(0,FONT_SIZE + 1);

    _textLvl.setFont(_font);
    _textLvl.setString("lvl : 0");
    _textLvl.setCharacterSize(FONT_SIZE);
    _textLvl.setPosition(0,(FONT_SIZE + 1)*2);

    _textGameOver.setFont(_font);
    _textGameOver.setString("Game Over");
    _textGameOver.setCharacterSize(72);
    _textGameOver.setPosition(0,0);
}

void Stats::gameOver() {
    _isGameOver = true;
}

void Stats::addLines(int lines) {
    if(lines > 0) {
        _nbRows += lines;
        // Essas deveriam estar abaixo do switch, nao?
        _textRows.setString("rows : " + std::to_string(_nbRows));
        _textScore.setString("score : " + std::to_string(_nbScore));
        switch (lines) {
            case 1: _nbScore += 40 * (_nbLvl+1); break;
            case 2: _nbScore += 100 * (_nbLvl+1); break;
            case 3: _nbScore += 300 * (_nbLvl+1); break;
            case 4: _nbScore += 1200 * (_nbLvl+1); break;
            default: break;
        }
        _nbLvl = _nbRows / 10;
        _textLvl.setString("lvl : " + std::to_string(_nbLvl));
    }
}

unsigned int Stats::getLvl()const{
    return _nbLvl;
}

void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (not _isGameOver) {
        states.transform *= getTransform();
        target.draw(_textRows, states);
        target.draw(_textScore, states);
        target.draw(_textLvl, states);
    } else
        target.draw(_textGameOver,states);
}
