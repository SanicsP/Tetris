#include "piece_grid.h"

#include <piece.h>



T_PieceGrid* T_PieceGrid_Create() {
    
    T_PieceGrid* new_grid;
    
    if( ( new_grid = malloc( sizeof(T_PieceGrid) ) ) == NULL ) 
        return NULL;
    

    if( ( new_grid->failling_piece = malloc( sizeof(T_Piece) ) ) == NULL ) 
        return NULL;
    
    memset(new_grid->pieces ,0 , GRID_WIDTH * GRID_HEIGHT * sizeof(int));

    new_grid->state = T_GS_INIT;

    return new_grid;

}

void T_PieceGrid_Destroy(T_PieceGrid* grid) {
    
    T_Piece_Destroy(grid->failling_piece);
    
    
    free(grid);

}

void T_PieceGrid_PastPiece(T_PieceGrid* grid , const T_Piece* piece) {

    
    for(int y_offset = 0 ; y_offset < T_PIECE_HEIGHT; y_offset++) {
        
        for(int x_offset = 0 ; x_offset < T_PIECE_WIDTH ; x_offset++)
        {
            grid->pieces[FLAT_2D(piece->position.x + x_offset , piece->position.y + y_offset , GRID_WIDTH)] = 
            piece->data[FLAT_3D(x_offset , y_offset , piece->orientation , T_PIECE_WIDTH , T_PIECE_HEIGHT)];
        }

    }

}


void T_PieceGrid_Update(T_PieceGrid* grid) 
{
    switch (grid->state)
    {
        case T_GS_INIT : {
            T_PieceGrid_NewPiece(grid , PT_J_PIECE);
            grid->state = T_GS_FALLING;
            break;
        }
        case T_GS_FALLING : {
            grid->state = T_Piece_TryTranslation(grid->failling_piece , PSIDE_DOWN , grid).new_state;

            if(grid->state == T_GS_UPDATE) {
                T_PieceGrid_PastPiece(grid , grid->failling_piece);
            }
            break;
        }
    
        case T_GS_UPDATE : 
        {
            printf("update state rechead\n");
            grid->state = T_PieceGrid_ReajustTokens(grid);
            break; 
        }

        case T_GS_REMOVE : {
            
            break;
        }
    }
}

void T_PieceGrid_NewPiece(T_PieceGrid* grid , int type) {
    
    T_Piece_Destroy(grid->failling_piece);
    grid->failling_piece = T_Piece_Create(type);

    printf("new piece created\n");

}

int T_PieceGrid_ReajustTokens(T_PieceGrid* grid) {
    
    T_Grid_State new_state;

    int reajustments = 1;
    int reajusted = 0;

    while (reajustments)
    {
        reajustments = 0;

        for(int y = 0; y < GRID_HEIGHT; y++) {
            
            for(int x = 0; x < GRID_WIDTH; x++) {
                int lower_y = y - 1;

                if (lower_y >= GRID_HEIGHT) break;

                int *token = &grid->pieces[FLAT_2D(x , y , GRID_WIDTH)];
                
                if(*token == EMPTY) break;

                int * lower_token = &grid->pieces[FLAT_2D(x , lower_y , GRID_WIDTH)];

                if (&lower_token == EMPTY) {
                    *token = EMPTY;
                    *lower_token = FILLED;
                    reajusted = 1;
                    reajustments = 1;
                }

            }

        }
    }

    return T_GS_INIT;
    
}

int T_PieceGrid_TryRemoveAlignedTokens(T_PieceGrid * grid) {

}