#include <iostream>

#include "game.hpp"
#include "configuration.hpp"

using namespace std;

int main(int argc,char* argv[])
{
    Configuration::initialize();

    Game game;
    game.run(60);

    return 0;
}
