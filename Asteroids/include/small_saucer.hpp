#ifndef _SMALL_SAUCER_HPP_
#define _SMALL_SAUCER_HPP_

#include "saucer.hpp"

class SmallSaucer : public Saucer {
  public :
    SmallSaucer(World& world);
    virtual int getPoints()const;
    virtual void update(sf::Time deltaTime);

  private:
    sf::Time _timeSinceLastShoot;
};

#endif
