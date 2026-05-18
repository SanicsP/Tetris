#include "renderer.h"





void renderer_init(Renderer* renderer) {

    renderer->origin = (sfVector2i){0 , 0};
    renderer->cell_size = RENDERER_CELL_SIZE;
    
    for(int y = 0 ; y < GRID_HEIGHT ; y++){

        for(int x = 0 ; x < GRID_WIDTH ; x++) 
        {
            sfRectangleShape* cell = (renderer->grid_cells[FLAT_2D(x , y , GRID_WIDTH)] = sfRectangleShape_create());
            
            if(!cell) {
                exit(EXIT_FAILURE); 
            }

            sfRectangleShape_setSize(cell , (sfVector2f){renderer->cell_size , renderer->cell_size});
            
            sfRectangleShape_setFillColor(cell , sfGreen);
            
            sfVector2f new_position;

            new_position.x = renderer->origin.x + renderer->cell_size* x;
            new_position.y = renderer->origin.y + renderer->cell_size* y;

            sfRectangleShape_setPosition(cell , new_position);

        }

    }

    for (int i = 0 ; i < T_PIECE_WIDTH*T_PIECE_HEIGHT ; i++) {
        sfRectangleShape* piece_cell = ( renderer->falling_piece_cells[i] = sfRectangleShape_create() );
    
        
        assert(piece_cell);

        sfRectangleShape_setFillColor(piece_cell , sfGreen);
        sfRectangleShape_setSize(piece_cell , (sfVector2f){renderer->cell_size , renderer->cell_size});


    }
    
}

void renderer_free_ressources(Renderer* renderer) {
    
    for(int i = 0 ; i < GRID_HEIGHT*GRID_WIDTH ; i++){
        sfRectangleShape_destroy(renderer->grid_cells[i]);
    }
}

void renderer_update_state(Renderer* renderer , const T_PieceGrid* grid){
    for(int y = 0 ; y < GRID_HEIGHT ; y++){

        for(int x = 0 ; x < GRID_WIDTH ; x++) 
        {
            int grid_cell = grid->pieces[FLAT_2D(x , y , GRID_WIDTH)];
            sfRectangleShape *rect = renderer->grid_cells[FLAT_2D(x , y , GRID_WIDTH)];

            if(grid_cell) {
                sfRectangleShape_setFillColor(rect , sfGreen);
                sfRectangleShape_setSize(rect , (sfVector2f){renderer->cell_size , renderer->cell_size});

            }
            else {
                sfRectangleShape_setFillColor(rect , sfBlack);
                sfRectangleShape_setSize(rect , (sfVector2f){0});
            }
        }

    }

    int n = 0;
    for(int y_offset = 0 ; y_offset < T_PIECE_HEIGHT ; y_offset++){

        for(int x_offset = 0 ; x_offset < T_PIECE_HEIGHT ; x_offset++) 
        {
            int index = FLAT_3D(x_offset , y_offset , grid->failling_piece->orientation , T_PIECE_WIDTH , T_PIECE_HEIGHT);
            
            int piece_cell = grid->failling_piece->data[index];
            // printf("piece_cell = %d\n" , piece_cell);
            
            sfRectangleShape *rect = renderer->grid_cells[FLAT_2D(x_offset , y_offset , T_PIECE_WIDTH)];
            
            sfRectangleShape_setPosition(rect , (sfVector2f) {
                    renderer->origin.x +(grid->failling_piece->position.x + x_offset)* renderer->cell_size ,
                    renderer->origin.y + (grid->failling_piece->position.y + y_offset)* renderer->cell_size 
                } );
            
            if(piece_cell) {
                sfRectangleShape_setFillColor(rect , sfGreen);
                sfRectangleShape_setSize(rect , (sfVector2f){renderer->cell_size , renderer->cell_size});
                
                
                n++;
            }
            else {
                sfRectangleShape_setFillColor(rect , sfBlack);
                sfRectangleShape_setSize(rect , (sfVector2f){0});

            }
        }



    }

    printf("num rendered : %d \n" , n);

    
}

void renderer_draw(Renderer* renderer , sfRenderWindow* render_window){
    
    for(int i = 0 ; i < T_PIECE_WIDTH*T_PIECE_HEIGHT ; i++){
        sfRenderWindow_drawRectangleShape(render_window ,renderer->falling_piece_cells[i] , NULL);
    }


    for(int i = 0 ; i < GRID_HEIGHT*GRID_WIDTH ; i++){
        sfRenderWindow_drawRectangleShape(render_window ,renderer->grid_cells[i] , NULL);
    }



}

