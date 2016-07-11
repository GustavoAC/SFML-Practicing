#include "big_saucer.hpp"
#include "world.hpp"

BigSaucer::BigSaucer(World& world) : Saucer(Configuration::Textures::BigSaucer, world) {
    _world.add(Configuration::Sounds::SaucerSpawn2);
    _impulse *= 300.f;
}

int BigSaucer::getPoints() const {
    return 100;
}

void BigSaucer::update(sf::Time deltaTime) {
    Saucer::update(deltaTime);
}
