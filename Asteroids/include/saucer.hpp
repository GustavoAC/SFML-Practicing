#ifndef _SAUCER_HPP_
#define _SAUCER_HPP_

#include <cmath>
#include "enemy.hpp"

class Saucer : public Enemy {
  public:
    Saucer(const Saucer&) = delete;
    Saucer& operator=(const Saucer&) = delete;
    using Enemy::Enemy; //Using the Enemy constructor

    virtual bool isCollide(const Entity& other) const;
    virtual void update(sf::Time deltaTime);
    virtual void onDestroy();
    static void newSaucer(World& world);
};

#endif
