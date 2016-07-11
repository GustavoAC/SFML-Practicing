#include "configuration.hpp"
#include "random.hpp"

// Instancia os statics
ResourceManager<sf::Texture,int> Configuration::textures;
ActionMap<int> Configuration::player_inputs;

void Configuration::initialize() {
    initTextures();
    initSounds();
    initPlayerInputs();
}

void Configuration::initTextures() {
    textures.load(Textures::PlayerTex, "media/Player/navinha.png");
}

void Configuration::initSounds() {

}

void Configuration::initPlayerInputs() {
    player_inputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
    player_inputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
    player_inputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
    player_inputs.map(PlayerInputs::Down, Action(sf::Keyboard::Down));
    player_inputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Z));
    player_inputs.map(PlayerInputs::Hyperspace, Action(sf::Keyboard::X));
}
