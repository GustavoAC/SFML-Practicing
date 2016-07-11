#ifndef _METEOR_HPP_
#define _METEOR_HPP_

#include "enemy.hpp"

class Meteor : public Enemy {
  public:
    Meteor(const Meteor&) = delete;
    Meteor& operator=(const Meteor&) = delete;
    using Enemy::Enemy;
    virtual bool isCollide(const Entity& other) const;
    virtual void update(sf::Time deltaTime);
};

class BigMeteor : public Meteor {
  public:
    BigMeteor(World& world);
    virtual int getPoints() const;
    virtual void onDestroy();
};

class MediumMeteor : public Meteor {
  public:
    MediumMeteor(World& world);
    virtual int getPoints() const;
    virtual void onDestroy();
};

class SmallMeteor : public Meteor {
  public:
    SmallMeteor(World& world);
    virtual int getPoints() const;
    virtual void onDestroy();
};

#endif
