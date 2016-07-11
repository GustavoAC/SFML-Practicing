#ifndef _BIG_SAUCER_HPP_
#define _BIG_SAUCER_HPP_

#include "saucer.hpp"

class BigSaucer : public Saucer {
  public :
    BigSaucer(World& world);
    virtual int getPoints()const;
    virtual void update(sf::Time deltaTime);
};

#endif
