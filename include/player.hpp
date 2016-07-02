#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "configuration.hpp"

class Player : public sf::Drawable, public ActionTarget<int> {
  public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player();

    template<typename ... Args>
    void setPosition(Args&& ... args) {
        _ship.setPosition(std::forward<Args>(args)...);
    }
    void processEvents();

    void update(sf::Time deltaTime);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite _ship;
    sf::Vector2f _velocity;

    bool _isMoving;
    int _rotation;
};

#endif
