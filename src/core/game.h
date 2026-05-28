#ifndef INCLUDE_GAME_HPP
#define INCLUDE_GAME_HPP

#include <stdio.h>
#include <CSFML/Graphics.h>

#include "renderer.h"

#include <piece.h>

#include <score_data.h>


#define GAME_FPS 10
#define WINDOW_WIDTH GRID_WIDTH*RENDERER_CELL_SIZE
#define WINDOW_HEIGHT GRID_HEIGHT*RENDERER_CELL_SIZE

typedef enum {
    GS_LAUNCH,
    GS_STATE_PLAYING,
    GS_RESTART, 
    GS_PAUSE, 
    GS_STOP 
} GameState;


typedef struct Game_S {
    
    GameState state;
    
    Renderer renderer;

    T_PieceGrid* tetris_grid;

    sfRenderWindow* window;

    sfEvent event;

    sfClock* clock;

    sfTime fall_rate;
    
    save_ScoreData player_data;


}Game;


void game_init(Game* game);

void game_free_ressources(Game* game);

void game_loop(Game* game);

void game_stop(Game* game);

void game_pause(Game* game);

void game_resume(Game* game);

void game_restart(Game * game);

GameState game_get_state(const Game* game);




#endif