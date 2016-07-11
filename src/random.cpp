#include <cstdlib>
#include "random.hpp"

float random(const float &min, const float &max) {
    return (rand()/float(RAND_MAX))*(max-min) + min;
}

int random(const int &min, const int &max) {
    return rand()%(max-min+1) + min;
}
