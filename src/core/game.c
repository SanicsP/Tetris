#include "game.h"


void game_init(Game* game) {
    
    game->window = sfRenderWindow_create((sfVideoMode){.size.x = WINDOW_WIDTH , .size.y = WINDOW_HEIGHT} , "CETRIS" , sfDefaultStyle , 0 , NULL);
    
    if(!game->window)
    {
        fprintf(stderr , "couldn't allocate the window\n");
        exit(EXIT_FAILURE);
    }

    sfRenderWindow_setFramerateLimit(game->window , GAME_FPS);

    renderer_init(&game->renderer);

    game->tetris_grid = T_PieceGrid_Create();

    if(!game->tetris_grid) {
        fprintf(stderr , "couldn't allocate the tetris grid\n");
        exit(EXIT_FAILURE);
    }
    
    game->clock = sfClock_create();
    game->fall_rate = sfMilliseconds(950.f);

    game->player_data = (save_ScoreData){0};

}

void game_free_ressources(Game* game){
    sfRenderWindow_destroy(game->window);
    renderer_free_ressources(&game->renderer);
    T_PieceGrid_Destroy(game->tetris_grid);
}

void game_loop(Game* game){
    
    //T_PieceGrid_NewPiece(game->tetris_grid , PT_J_PIECE);
    // T_Piece_TryRotation(game->tetris_grid->failling_piece , 1 , game->tetris_grid);


    while (sfRenderWindow_isOpen(game->window))
    {
        while(sfRenderWindow_pollEvent(game->window , &game->event)) {
            if(game->event.type == sfEvtClosed) {
                sfRenderWindow_close(game->window);
            }
        }

        
        
        //T_Piece_TryTranslation(game->tetris_grid->failling_piece , PSIDE_DOWN , game->tetris_grid);
        int query_rotation = 0;
        int query_translation = -1;

        if(sfKeyboard_isKeyPressed(sfKeyRight)) {
            query_translation = PSIDE_RIGHT;
        }
        else if(sfKeyboard_isKeyPressed(sfKeyLeft)) {
            query_translation = PSIDE_LEFT;
        }
        else if(sfKeyboard_isKeyPressed(sfKeyDown)) {
            query_translation = PSIDE_DOWN;
        }
        
        if (sfKeyboard_isKeyPressed(sfKeyUp)) {
            query_rotation = 1;
        }

        int update_result = T_PieceGrid_Update(game->tetris_grid , query_rotation , query_translation);
        
        sfRenderWindow_clear(game->window , sfBlack);
        
        renderer_update_state(&game->renderer , game->tetris_grid);
        
        renderer_draw(&game->renderer , game->window);

        sfRenderWindow_display(game->window);

        if(!update_result) {
            game_restart(game);
        }

        switch (update_result)
        {
            case 2 :
                save_ScoreData_IncreaseScore(&game->player_data , 1);
                printf("[GAME] Score : %u\n" , game->player_data.score);
            break;
        
            default:
                break;
        }

    }
    
}

void game_stop(Game* game){
    game->state = GS_STOP;
    game_free_ressources(game);
    sfRenderWindow_close(game->window);
}

void game_pause(Game* game){
    game->state = GS_PAUSE;
}

void game_resume(Game* game){
    game->state = GS_STATE_PLAYING;
}

void game_restart(Game * game) {
    game_free_ressources(game);

    game_init(game);

}
GameState game_get_state(const Game* game){

}
