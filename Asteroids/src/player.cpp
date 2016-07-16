#include "player.hpp"
#include "random.hpp"
#include "shoot.hpp"

Player::Player(World& world) : Entity(Configuration::Textures::PlayerTex, world),
                               ActionTarget(Configuration::player_inputs),
                               _isMoving(false),
                               _rotation(0) {
    this->setPosition(300, 300);

    bind(Configuration::PlayerInputs::Up, [this](const sf::Event&){
        _isMoving = true;
    });

    bind(Configuration::PlayerInputs::Left, [this](const sf::Event&){
        _rotation-= 1;
    });

    bind(Configuration::PlayerInputs::Right, [this](const sf::Event&){
        _rotation+= 1;
    });

    bind(Configuration::PlayerInputs::Down, [this](const sf::Event&){
        this->setPosition(300, 300);
    });

    bind(Configuration::PlayerInputs::Shoot,[this](const sf::Event&){
        shoot();
    });

    bind(Configuration::PlayerInputs::Hyperspace,[this](const sf::Event&){
        goToHyperspace();
    });
}

void Player::processEvents(){
    _isMoving = false;
    _rotation = 0;
    ActionTarget<int>::processEvents();
}

void Player::update(sf::Time deltaTime) {
    float seconds = deltaTime.asSeconds();
    _timeSinceLastShoot += deltaTime;

    if (_rotation != 0) {
        float angle = _rotation*250*seconds; //300 is the rotation speed
        _sprite.rotate(angle);
    }

    if (_isMoving) {
        float angle = _sprite.getRotation() / 180 * M_PI /*- M_PI / 2*/;
        _impulse += sf::Vector2f(std::cos(angle),std::sin(angle)) * 300.f
        * seconds; //300 is the acceleration
    }

    _sprite.move(seconds * _impulse);
}

/*
Double dispatching makes this faster (although it's harder to implement)
Double dispatching is a way to "discover" exactly what type is going into the
function in a OOP environment. Basically one object calls a function to another
so in the end both of them are defined real classes.
*/
bool Player::isCollide(const Entity& other)const {
    if (dynamic_cast<const ShootPlayer*>(&other) == nullptr) {
        return Collision::circleTest(_sprite,other._sprite);
    }
    return false;
}

void Player::shoot() {
    // Comment this later to have some fun.
    if (_timeSinceLastShoot > sf::seconds(0.3)) {
        _world.add(new ShootPlayer(*this));
        _timeSinceLastShoot = sf::Time::Zero;
    }
}

void Player::goToHyperspace() {
    _impulse = sf::Vector2f(0,0);
    setPosition(random(0,_world.getX()),random(0,_world.getY()));
    _world.add(Configuration::Sounds::Jump);
}

void Player::onDestroy() {
    Entity::onDestroy();
    Configuration::player = nullptr;
    Configuration::_lives--;
    _world.add(Configuration::Sounds::Boom);
}
