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
            int piece_tok_index = FLAT_3D(x_offset , y_offset , piece->orientation , T_PIECE_WIDTH , T_PIECE_HEIGHT);
            int grid_tok_index = FLAT_2D(piece->position.x + x_offset , piece->position.y + y_offset , GRID_WIDTH);

            if(piece->data[piece_tok_index]) {
                grid->pieces[grid_tok_index] = sfColor_toInteger(piece->color); 
            }
        }

    }

}


void T_PieceGrid_Update(T_PieceGrid* grid , int query_rotation , int query_translation) 
{
    switch (grid->state)
    {
        case T_GS_INIT : {
            T_PieceGrid_NewPiece(grid , rand() % 7);
            grid->state = T_GS_FALLING;
            break;
        }
        case T_GS_FALLING : {
            
            T_Piece_TryRotation(grid->failling_piece , query_rotation , grid);
            
            grid->state = T_Piece_TryTranslation(grid->failling_piece , query_translation , grid).new_state;

            if(grid->state == T_GS_UPDATE) {
                T_PieceGrid_PastPiece(grid , grid->failling_piece);
                break;
            }

            grid->state = T_Piece_TryTranslation(grid->failling_piece , PSIDE_DOWN , grid).new_state;


            if(grid->state == T_GS_UPDATE) {
                T_PieceGrid_PastPiece(grid , grid->failling_piece);
                break;
            }

            break;
        }
    
        case T_GS_UPDATE : 
        {
            //printf("update state rechead\n");
            //grid->state = T_PieceGrid_ReajustTokens(grid);
            grid->state = T_GS_REMOVE;
            break; 
        }

        case T_GS_REMOVE : {
            grid->state = T_PieceGrid_TryRemoveAlignedTokens(grid);
            break;
        }
    }
}

void T_PieceGrid_NewPiece(T_PieceGrid* grid , int type) {
    
    T_Piece_Destroy(grid->failling_piece);
    grid->failling_piece = T_Piece_Create(type);

    //printf("new piece created\n");

}

int T_PieceGrid_ReajustTokens(T_PieceGrid* grid) {
    
    T_Grid_State new_state;

    int reajustments = 1;
    int reajusted = 0;

    // printf("trying to reajust tokens\n");

    while (reajustments)
    {
        reajustments = 0;

        for(int y = 0; y < GRID_HEIGHT-1; y++) {
            
            for(int x = 0; x < GRID_WIDTH; x++) {
                
                int token_idx = FLAT_2D(x , y , GRID_WIDTH);

                int token = grid->pieces[token_idx];

                int lower_token_idx = FLAT_2D(x , y + 1 , GRID_WIDTH);
                
                int lower_token = grid->pieces[lower_token_idx];

                
                if (token && !lower_token) {
                    grid->pieces[token_idx] = EMPTY;
                    grid->pieces[lower_token_idx] = FILLED;
                    reajusted = 1;
                    reajustments = 1;
                    //printf("\t reajusted\n");
                }

            }

        }
    }

    return T_GS_REMOVE;
    
}

int T_PieceGrid_TryRemoveAlignedTokens(T_PieceGrid * grid) {
    
    int row_removed = 0;

    int row_height = 0;

    int at_least_one_empty = 0;

    // printf("attempt to remove a row\n");

    for(int y = GRID_HEIGHT - 1 ; y >= 0 ; y--) {
        
        at_least_one_empty = 0;

        for(int x = 0 ; x < GRID_WIDTH ; x++ ) {
            if(!grid->pieces[FLAT_2D(x , y , GRID_WIDTH)]) at_least_one_empty = 1;
        }

        if(!at_least_one_empty) {
            row_removed = 1;
            row_height = y;
            for(int x = 0 ; x < GRID_WIDTH ; x++) {
                grid->pieces[FLAT_2D(x , y , GRID_WIDTH)] = T_EMPTY;
            }
            // printf("\t row removed\n");

            break;
        }
        else {
            // printf("\t at least one empty in the row %d\n" , y );
        }
    }

    if(row_removed) T_PieceGrid_ShrinkTokens(grid , row_height);

    return row_removed ? T_GS_REMOVE : T_GS_INIT; 
}

int T_PieceGrid_ShrinkTokens(T_PieceGrid* grid  , int removed_row) {


    for(int y = removed_row - 1; y > 0 ; y--) {
        // printf("row reajusted\n");
        for(int x = 0 ; x < GRID_WIDTH ; x++) 
        {
            
            int piece_idx  = FLAT_2D(x , y , GRID_WIDTH);
            int low_piece_idx = FLAT_2D(x , y + 1 , GRID_WIDTH);
            
            grid->pieces[low_piece_idx] = grid->pieces[piece_idx];
            grid->pieces[piece_idx] = T_EMPTY;

        }

    }

    // printf("tokens shrinked\n");

}
