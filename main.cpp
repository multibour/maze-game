#include <SFML/Graphics.hpp>
#include <ctime>

#include "game.h"

int main(){
    srand(time(NULL));

    Game game;

    game.run();

    return 0;
}

