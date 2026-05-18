#include "main.h"
#include "game.h"

#include "../tetris/tetris.h"

#include <stdio.h>
#include <tetris_tests.h>

int main() {

    //tetris_unit_tests();
    
    Game game;

    game_init(&game);
    
    game_loop(&game);

    game_free_ressources(&game);
    
    return 0;
}