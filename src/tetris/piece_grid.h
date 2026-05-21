#ifndef INCLUDE_PIECE_GRID_H
#define INCLUDE_PIECE_GRID_H




#define FILLED     1
#define EMPTY      0

#define GRID_WIDTH 15
#define GRID_HEIGHT 30

#include <stdlib.h>
#include <string.h>
#include <utils.h>

#define T_FLATTEN_GRID(x ,y) x + y*GRID_WIDTH


typedef struct T_Piece_S T_Piece;

typedef enum {
    T_GS_INIT,
    T_GS_FALLING , 
    T_GS_UPDATE ,
    T_GS_REMOVE  
} T_Grid_State;

typedef struct T_PieceGrid_S {
    T_Grid_State state;
    T_Piece* failling_piece;
    int pieces[GRID_WIDTH*GRID_HEIGHT];
} T_PieceGrid;


T_PieceGrid* T_PieceGrid_Create();

void T_PieceGrid_Destroy(T_PieceGrid* grid);


/*
    irrelevant function, it cause the failling piece to overlap with himself, 
    solution : only past the tokens directly to the grid when the piece is broken , 
    render the piece separately from the tetris grid. 
*/
void T_PieceGrid_PastPiece(T_PieceGrid* grid , const T_Piece* piece);

void T_PieceGrid_Update(T_PieceGrid* grid , int query_rotation , int query_translation);

void T_PieceGrid_NewPiece(T_PieceGrid* grid , int type);

int T_PieceGrid_ReajustTokens(T_PieceGrid* grid);


int T_PieceGrid_TryRemoveAlignedTokens(T_PieceGrid * grid);

int T_PieceGrid_ShrinkTokens(T_PieceGrid* grid  , int removed_row);


#endif