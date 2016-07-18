#ifndef _STATS_HPP_
#define _STATS_HPP_

#include <SFML/Graphics.hpp>

class Stats : public sf::Transformable, public sf::Drawable {
  public:
    Stats();
    void addLines(int lines);
    unsigned int getLvl()const;
    void gameOver();

  private:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states=sf::RenderStates::Default) const override;

    unsigned int _nbRows;
    unsigned int _nbScore;
    unsigned int _nbLvl;
    bool _isGameOver;

    sf::Text _textRows;
    sf::Text _textScore;
    sf::Text _textLvl;
    sf::Text _textGameOver;
    sf::Font _font;
};

#endif
