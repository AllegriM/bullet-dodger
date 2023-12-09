#include <iostream>
#include "Game.h"

int main()

{
    Game game;

    std::srand(static_cast<unsigned>(time(NULL)));

    while (game.running())
    {
        game.update();

        game.render();
    }
    return 0;
}