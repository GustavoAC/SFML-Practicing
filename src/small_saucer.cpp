#include "small_saucer.hpp"
#include "world.hpp"
#include "shoot.hpp"

SmallSaucer::SmallSaucer(World& world) : Saucer(Configuration::Textures::SmallSaucer, world) {
    _timeSinceLastShoot = sf::Time::Zero;
    _world.add(Configuration::Sounds::SaucerSpawn2);
    _impulse *= 400.f;
}

int SmallSaucer::getPoints() const {
    return 200;
}

void SmallSaucer::update(sf::Time deltaTime) {
    Saucer::update(deltaTime);
    _timeSinceLastShoot += deltaTime;
    if(_timeSinceLastShoot > sf::seconds(1.5)) {
        if(Configuration::player != nullptr)
            _world.add(new ShootSaucer(*this));
        _timeSinceLastShoot = sf::Time::Zero;
    }
}
