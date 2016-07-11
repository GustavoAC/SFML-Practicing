#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "action_target.hpp"
#include "entity.hpp"
#include "world.hpp"

class Player : public Entity, public ActionTarget<int> {
  public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(World& world);

    virtual bool isCollide(const Entity& other) const;
    virtual void update(sf::Time deltaTime);
    void processEvents();
    void shoot();
    void goToHyperspace();
    virtual void onDestroy();

  private:
    bool _isMoving;
    int _rotation;
    sf::Time _timeSinceLastShoot;
};

#endif
