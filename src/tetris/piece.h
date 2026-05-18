#ifndef INCLUDE_PIECE_H
#define INCLUDE_PIECE_H

#include <CSFML/Graphics.h>

#include <stdio.h>
#include <stdlib.h>

#include <tetris_constants.h>





#define O_PIECE {               \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0               \
    }   

#define I_PIECE {               \
    0 , 0 , 0 , 0 ,             \
    1 , 1 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
    1 , 1 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 1 , 0 , 0 ,             \
    0 , 1 , 0 , 0 ,             \
    0 , 1 , 0 , 0 ,             \
    0 , 1 , 0 , 0 ,             \
    }

#define S_PIECE {               \
    0 , 0 , 1 , 1 ,             \
    0 , 1 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 1 , 1 , 0 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 1 , 0 , 0 ,             \
    0 , 1 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    }

#define Z_PIECE {               \
    0 , 1 , 1 , 0 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 0 , 1 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 1 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 1 , 0 , 0 ,             \
    0 , 1 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
    }

#define J_PIECE {               \
    0 , 1 , 0 , 0 ,             \
    0 , 1 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 1 , 1 , 1 ,             \
    0 , 0 , 0 , 1 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 1 , 1 , 0               \
    }

#define L_PIECE {               \
    0 , 0 , 0 , 1 ,             \
    0 , 0 , 0 , 1 ,             \
    0 , 1 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 0 , 0 ,             \
    0 , 1 , 1 , 1 ,             \
    0 , 1 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 1 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 0 , 0               \
    }

#define T_PIECE {               \
    0 , 0 , 1 , 0 ,             \
    0 , 1 , 1 , 1 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 1 , 1 , 1 ,             \
    0 , 0 , 1 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
    0 , 0 , 0 , 0 ,             \
                                \
    0 , 0 , 0 , 1 ,             \
    0 , 0 , 1 , 1 ,             \
    0 , 0 , 0 , 1 ,             \
    0 , 0 , 0 , 0               \
    }
    

typedef enum {
    PT_O_PIECE = 0 ,
    PT_I_PIECE ,
    PT_S_PIECE ,
    PT_Z_PIECE ,
    PT_L_PIECE ,
    PT_J_PIECE ,
    PT_T_PIECE 
} T_PieceType;

typedef enum {
    PS_FALLING , 
    PS_BROKEN
} T_PieceState;

typedef enum {
    PSIDE_RIGHT,
    PSIDE_DOWN,
    PSIDE_LEFT,
    PSIDE_UP
} T_PieceSide;

typedef int T_PiecesData[T_PIECES_SIZE];

typedef struct T_Piece_S {
    T_PieceType type;
    T_PieceState state;
    T_PiecesData data;
    T_PieceSide orientation;
    sfVector2i position;
}T_Piece;

typedef struct T_PieceTransformResult_S {
    int new_state;
    int is_valid;
}T_PieceTransformResult;

typedef struct T_PieceGrid_S T_PieceGrid;




T_Piece* T_Piece_Create(T_PieceType piece_type);

void T_Piece_Destroy(T_Piece* piece);


T_PieceTransformResult T_Piece_TryRotation(T_Piece* piece , int positive , T_PieceGrid* grid);

T_PieceTransformResult T_Piece_TryTranslation(T_Piece* piece , T_PieceSide side , T_PieceGrid* grid);

int T_Piece_IsOverlaping(sfVector2i new_position , int new_rotation , const T_Piece* piece , const T_PieceGrid* grid);

int T_Piece_IsOutOfBounds(sfVector2i new_position , int new_rotation , const T_Piece* piece , const T_PieceGrid* grid);

void T_ShowPieces(const T_PiecesData pieces);



#endif