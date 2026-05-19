#include "game.h"


void game_init(Game* game) {
    
    game->window = sfRenderWindow_create((sfVideoMode){.size.x = 400 , .size.y = 400} , "TETRIS" , sfDefaultStyle , 0 , NULL);
    
    if(!game->window)
    {
        fprintf(stderr , "couldn't allocate the window\n");
        exit(EXIT_FAILURE);
    }

    sfRenderWindow_setFramerateLimit(game->window , 20);

    renderer_init(&game->renderer);

    game->tetris_grid = T_PieceGrid_Create();

    if(!game->tetris_grid) {
        fprintf(stderr , "couldn't allocate the tetris grid\n");
        exit(EXIT_FAILURE);
    }
    

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
        
        if(sfKeyboard_isKeyPressed(sfKeyRight)) {
            T_Piece_TryTranslation(game->tetris_grid->failling_piece , PSIDE_RIGHT , game->tetris_grid);
        }
        else if(sfKeyboard_isKeyPressed(sfKeyLeft)) {
            T_Piece_TryTranslation(game->tetris_grid->failling_piece , PSIDE_LEFT , game->tetris_grid);
        }
        else if (sfKeyboard_isKeyPressed(sfKeyA)) {
            T_Piece_TryRotation(game->tetris_grid->failling_piece , -1 , game->tetris_grid);
        }
        else if (sfKeyboard_isKeyPressed(sfKeyZ)) {
            T_Piece_TryRotation(game->tetris_grid->failling_piece , 1 , game->tetris_grid);
        }



        T_PieceGrid_Update(game->tetris_grid);
        
        sfRenderWindow_clear(game->window , sfBlack);
        
        renderer_update_state(&game->renderer , game->tetris_grid);
        
        renderer_draw(&game->renderer , game->window);

        sfRenderWindow_display(game->window);
    }
    
}

void game_stop(Game* game){

}

void game_pause(Game* game){

}

void game_resume(Game* game){

}

GameState game_get_state(const Game* game){

}