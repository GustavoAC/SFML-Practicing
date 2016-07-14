#include "saucer.hpp"
#include "shoot.hpp"
#include "player.hpp"
#include "meteor.hpp"
#include "collision.hpp"
#include "world.hpp"
#include "random.hpp"
#include "big_saucer.hpp"
#include "small_saucer.hpp"

bool Saucer::isCollide(const Entity& other) const {
    if (dynamic_cast<const ShootSaucer*>(&other) == nullptr) {
        return Collision::circleTest(_sprite, other._sprite);
    }
    return false;
}

void Saucer::update(sf::Time deltaTime) {
    float seconds = deltaTime.asSeconds();
    Entity* near = nullptr;
    float near_distance = 300;

    // Gets the nearest Meteor or ShootPlayer
    for (Entity* entity_ptr : _world.getEntities()) {
        if (entity_ptr != this and (dynamic_cast<const Meteor*>(entity_ptr) or
        dynamic_cast<const ShootPlayer*>(entity_ptr))) {
            float x = getPosition().x - entity_ptr->getPosition().x;
            float y = getPosition().y - entity_ptr->getPosition().y;
            float dist = std::sqrt(x*x + y*y);
            if (dist < near_distance) {
                near_distance = dist;
                near = entity_ptr;
            }
        }
    }

    // Gets away rapidly from Meteor/bullet if it exists. Otherwise goes for player slowly
    // atan2 is a pretty neat function.
    if (near != nullptr) {
        sf::Vector2f pos = near->getPosition() - getPosition();
        float angle_rad = std::atan2(pos.y, pos.x); //arc tangent of y/x
        _impulse -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 300.f
        * seconds;
    } else {
        sf::Vector2f pos = Configuration::player->getPosition() - getPosition();
        float angle_rad = std::atan2(pos.y,pos.x);
        _impulse += sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f
        * seconds;
    }

    _sprite.move(seconds * _impulse);
}

void Saucer::onDestroy() {
    Enemy::onDestroy();
    _world.add(Configuration::Sounds::Boom2);
}

void Saucer::newSaucer(World& world) {
    Saucer* res = nullptr;
    if(random(0.f,1.f) > Configuration::getScore()/20000.f)
        res = new BigSaucer(world);
    else
        res = new SmallSaucer(world);

    res->setPosition(0, random(0.f,(float)world.getY()));
    world.add(res);
}
