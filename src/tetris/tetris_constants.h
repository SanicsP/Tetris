#ifndef TETRIS_CONSTANTS_H
#define TETRIS_CONSTANTS_H

#define T_PIECE_WIDTH           4
#define T_PIECE_HEIGHT          4
#define T_PIECE_ROTATIONS       4

#define T_FLATTEN_DATA(x , y , o) (x) + (y)*T_PIECE_WIDTH + (o)*T_PIECE_WIDTH*T_PIECE_HEIGHT
#define T_FLATTEN_DATA_2D(x , y) (x) + (y)*T_PIECE_WIDTH


#define T_PIECES_SIZE       T_PIECE_WIDTH*T_PIECE_HEIGHT*T_PIECE_ROTATIONS

#define T_RIGHT_ROTATION        0
#define T_DOWN_ROTATION         1
#define T_LEFT_ROTATION         2
#define T_UP_ROTATION           3

#define T_FILLED                1
#define T_EMPTY                 0

#define T_POSITIVE              1
#define T_NEGATIVE             -1


#endif