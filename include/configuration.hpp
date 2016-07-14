#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resource_manager.hpp"
#include "action_map.hpp"

class Player;

class Configuration {
  public:
    Configuration() = delete;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    static Player* player;
    static int _lives;

    static void initialize();
    static void draw(sf::RenderTarget& target);

    static int getScore();
    static void addScore(int s);
    static bool isGameOver();

    enum Textures : int {PlayerTex,
                        PlayerLife,
                        BigSaucer,
                        SmallSaucer,
                        BigMeteor1,
                        BigMeteor2,
                        BigMeteor3,
                        BigMeteor4,
                        MediumMeteor1,
                        MediumMeteor2,
                        SmallMeteor1,
                        SmallMeteor2,
                        SmallMeteor3,
                        SmallMeteor4,
                        ShootPlayer,
                        ShootSaucer};
    static ResourceManager<sf::Texture, int> textures;

    enum Sounds : int {LaserPlayer,
                    LaserEnemy,
                    SaucerSpawn1,
                    SaucerSpawn2,
                    Boom,
                    Boom2,
                    Explosion1,
                    Explosion2,
                    Explosion3,
                    Jump};
    static ResourceManager<sf::SoundBuffer, int> sounds;

    enum Fonts : int {Gui};
    static ResourceManager<sf::Font, int> fonts;

    enum PlayerInputs : int {Up,
                            Left,
                            Right,
                            Down,
                            Shoot,
                            Hyperspace};
    static ActionMap<int> player_inputs;

  private:
    static int _score;
    static sf::Text   _txt_score;
    static sf::Sprite _spr_life;

    static void initTextures();
    static void initFonts();
    static void initSounds();
    static void initPlayerInputs();
};

#endif
