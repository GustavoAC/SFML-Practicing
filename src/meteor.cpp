#include "meteor.hpp"
#include "world.hpp"
#include "collision.hpp"
#include "random.hpp"

bool Meteor::isCollide(const Entity& other)const {
    if(dynamic_cast<const Meteor*>(&other) == nullptr) {
        return Collision::circleTest(_sprite,other._sprite);
    }
    return false;
}

void Meteor::update(sf::Time deltaTime) {
    float seconds = deltaTime.asSeconds();
    _sprite.move(seconds * _impulse);
}

//Big Meteor//

BigMeteor::BigMeteor(World& world) :
    Meteor((Configuration::Textures)random(Configuration::Textures::BigMeteor1,
                                           Configuration::Textures::BigMeteor4), world) {
    _impulse *= 100.f;
}

int BigMeteor::getPoints() const {
    return 20;
}

void BigMeteor::onDestroy() {
    Meteor::onDestroy();
    int nb = random(2,3);
    for(int i=0;i<nb;++i) {
        MediumMeteor* meteor = new MediumMeteor(_world);
        meteor->setPosition(getPosition());
        _world.add(meteor);
    }
    _world.add(Configuration::Sounds::Explosion1);
}

//Medium Meteor//

MediumMeteor::MediumMeteor(World& world) :
    Meteor((Configuration::Textures)random(Configuration::Textures::MediumMeteor1,
                                           Configuration::Textures::MediumMeteor2), world) {
    _impulse *= 150.f;
}

int MediumMeteor::getPoints() const {
    return 60;
}

void MediumMeteor::onDestroy() {
    Meteor::onDestroy();
    int nb = random(2,3);
    for(int i=0;i<nb;++i) {
        SmallMeteor* meteor = new SmallMeteor(_world);
        meteor->setPosition(getPosition());
        _world.add(meteor);
    }
    _world.add(Configuration::Sounds::Explosion1);
}

//Small Meteor//

SmallMeteor::SmallMeteor(World& world) :
    Meteor((Configuration::Textures)random(Configuration::Textures::SmallMeteor1,
                                           Configuration::Textures::SmallMeteor4), world) {
    _impulse *= 200.f;
}

int SmallMeteor::getPoints() const {
    return 100;
}

void SmallMeteor::onDestroy() {
    Meteor::onDestroy();
    _world.add(Configuration::Sounds::Explosion1);
}
