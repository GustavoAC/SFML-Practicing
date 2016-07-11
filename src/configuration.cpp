#include "configuration.hpp"
#include "random.hpp"

// Instancia os statics
ResourceManager<sf::Texture,int> Configuration::textures;
ResourceManager<sf::SoundBuffer,int> Configuration::sounds;
ActionMap<int> Configuration::player_inputs;
Player* Configuration::player = nullptr;
int Configuration::_score;

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

int Configuration::getScore(){
    return Configuration::_score;
}

void Configuration::addScore(int s){
    Configuration::_score += s;
}
