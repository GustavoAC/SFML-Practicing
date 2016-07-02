#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include "resource_manager.hpp"
#include "classes.hpp"
#include "action.hpp"
#include "action_target.hpp"
#include "action_map.hpp"

class Configuration {
  public:
    Configuration() = delete;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    enum Textures : int {Player};
    static ResourceManager<sf::Texture, int> textures;

    enum PlayerInputs : int {Up,Left,Right,Down};
    static ActionMap<int> player_inputs;

    static void initialize();

  private:
    static void initTextures();
    static void initPlayerInputs();
};

#endif
