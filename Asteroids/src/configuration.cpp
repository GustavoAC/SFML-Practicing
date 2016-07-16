#include "configuration.hpp"
#include "random.hpp"

// Instancia os statics
ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds;
ResourceManager<sf::Font, int> Configuration::fonts;
ActionMap<int> Configuration::player_inputs;

Player* Configuration::player = nullptr;
int Configuration::_score;
int Configuration::_lives = 3;
sf::Text   Configuration::_txt_score;
sf::Sprite Configuration::_spr_life;

void Configuration::initialize() {
    initTextures();
    initFonts();
    initSounds();
    initPlayerInputs();

    _txt_score.setFont(fonts.get(Fonts::Gui));
    _txt_score.setCharacterSize(24);
    _txt_score.setString("Score: 0");

    _spr_life.setTexture(textures.get(Textures::PlayerLife));
}

void Configuration::initTextures(){
    //player
    textures.load(Textures::PlayerTex,"media/Player/navinha.png");
    textures.load(Textures::PlayerLife,"media/Player/life.png");
    //saucers
    textures.load(Textures::BigSaucer,"media/Saucer/Big.png");
    textures.load(Textures::SmallSaucer,"media/Saucer/Small.png");
    //meteors
    textures.load(Textures::BigMeteor1,"media/Meteor/Big1.png");
    textures.load(Textures::BigMeteor2,"media/Meteor/Big2.png");
    textures.load(Textures::BigMeteor3,"media/Meteor/Big3.png");
    textures.load(Textures::BigMeteor4,"media/Meteor/Big4.png");

    textures.load(Textures::MediumMeteor1,"media/Meteor/Medium1.png");
    textures.load(Textures::MediumMeteor2,"media/Meteor/Medium2.png");

    textures.load(Textures::SmallMeteor1,"media/Meteor/Small1.png");
    textures.load(Textures::SmallMeteor2,"media/Meteor/Small2.png");
    textures.load(Textures::SmallMeteor3,"media/Meteor/Small3.png");
    textures.load(Textures::SmallMeteor4,"media/Meteor/Small4.png");
    //lasers
    textures.load(Textures::ShootPlayer,"media/Shoot/Player.png");
    textures.load(Textures::ShootSaucer,"media/Shoot/Saucer.png");
}

void Configuration::initFonts() {
    fonts.load(Fonts::Gui, "media/font/OpenSans.ttf");
}

void Configuration::initSounds() {
    //laser
    sounds.load(Sounds::LaserPlayer,"media/sounds/laser1.ogg");
    sounds.load(Sounds::LaserEnemy,"media/sounds/laser2.ogg");
    //saucers
    sounds.load(Sounds::SaucerSpawn1,"media/sounds/spawn1.flac");
    sounds.load(Sounds::SaucerSpawn2,"media/sounds/spawn2.flac");
    // Boom
    sounds.load(Sounds::Boom,"media/sounds/boom.flac");
    sounds.load(Sounds::Boom2,"media/sounds/boom2.flac");
    // Explosion
    sounds.load(Sounds::Explosion1,"media/sounds/explosion1.flac");
    sounds.load(Sounds::Explosion2,"media/sounds/explosion2.flac");
    sounds.load(Sounds::Explosion3,"media/sounds/explosion3.flac");
    //others
    sounds.load(Sounds::Jump,"media/sounds/hyperspace.flac");
}

void Configuration::initPlayerInputs() {
    player_inputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
    player_inputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
    player_inputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
    player_inputs.map(PlayerInputs::Down, Action(sf::Keyboard::Down));
    player_inputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Z));
    player_inputs.map(PlayerInputs::Hyperspace, Action(sf::Keyboard::X));
}

bool Configuration::isGameOver(){
    return (_lives <= 0);
}

int Configuration::getScore(){
    return Configuration::_score;
}

void Configuration::addScore(int s){
    Configuration::_score += s;
    _txt_score.setString("Score: " + std::to_string(_score));
}

void Configuration::draw(sf::RenderTarget& target) {
    target.draw(_txt_score);
    for(int i = 0;i < _lives;++i) {
        _spr_life.setPosition(40*i, 40);
        target.draw(_spr_life);
    }
}
