#ifndef _COLLISION_HPP_
#define _COLLISION_HPP_

#include <SFML/Graphics.hpp>

class Collision {
  public:
    Collision() = delete;
    Collision(const Collision&) = delete;
    Collision& operator=(const Collision&) = delete;

    static bool circleTest(const sf::Sprite& first, const sf::Sprite& second);
};

#endif
