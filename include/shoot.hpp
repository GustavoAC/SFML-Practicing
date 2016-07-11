#ifndef _SHOOT_HPP_
#define _SHOOT_HPP_

#include "entity.hpp"
#include "player.hpp"
#include "saucer.hpp"
#include "collision.hpp"

class Shoot : public Entity {
  public:
    Shoot(const Shoot&) = delete;
    Shoot& operator=(const Shoot&) = delete;
    using Entity::Entity;
    virtual void update(sf::Time deltaTime);
  protected:
    sf::Time _duration;
};

class ShootPlayer : public Shoot {
  public:
    ShootPlayer(const ShootPlayer&) = delete;
    ShootPlayer& operator=(const ShootPlayer&) = delete;
    ShootPlayer(Player& from);
    virtual bool isCollide(const Entity& other)const;
};

class ShootSaucer : public Shoot {
  public:
    ShootSaucer(const ShootSaucer&) = delete;
    ShootSaucer& operator=(const ShootSaucer&) = delete;
    ShootSaucer(Saucer& from);
    virtual bool isCollide(const Entity& other)const;
};

#endif
