#include "player.hpp"

Player::Player() : ActionTarget(Configuration::player_inputs),
                  _isMoving(false),
                  _rotation(0) {
    _ship.setTexture(Configuration::textures.get(Configuration::Textures::Player));
    _ship.setOrigin(32,32);
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
}

void Player::processEvents(){
    _isMoving = false;
    _rotation = 0;
    ActionTarget<int>::processEvents();
}

void Player::update(sf::Time deltaTime) {
    float seconds = deltaTime.asSeconds();

    if (_rotation != 0) {
        float angle = _rotation*300*seconds; //300 is the rotation speed
        _ship.rotate(angle);
    }

    if (_isMoving) {
        float angle = _ship.getRotation() / 180 * M_PI;
        _velocity += sf::Vector2f(std::cos(angle),std::sin(angle)) *
        100.f * seconds; //100 is the acceleration
    }

    _ship.move(seconds * _velocity);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_ship, states);
}
