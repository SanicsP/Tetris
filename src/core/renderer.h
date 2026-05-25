#ifndef __INCLUDE_RENDERER_H__
#define __INCLUDE_RENDERER_H__

#include "../tetris/tetris_constants.h"
#include "../tetris/piece_grid.h"
#include "../tetris/piece.h"

#include "utils.h"

#include <CSFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RENDERER_CELL_SIZE 20 


typedef struct Renderer_S {
    sfRectangleShape* grid_cells[GRID_WIDTH*GRID_HEIGHT];
    sfRectangleShape* falling_piece_cells[T_PIECE_WIDTH*T_PIECE_HEIGHT];
    sfVector2i origin;
    int cell_size;

    sfVertexArray* border_lines;

} Renderer;


void renderer_init(Renderer* renderer);

void renderer_free_ressources(Renderer* renderer);

void renderer_update_state(Renderer* renderer , const T_PieceGrid* grid);

void renderer_draw(Renderer* renderer , sfRenderWindow* render_window);

void renderer_draw_falling_piece(const Renderer* renderer , const T_PieceGrid * grid , sfRenderWindow* render_window);





#endif