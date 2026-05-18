#include "piece.h"
#include "piece_grid.h"

#include <string.h>



static sfVector2i T_Side_To_Offset(T_PieceSide side) {
    switch(side) {
        case PSIDE_RIGHT :
            return (sfVector2i){1 , 0}; 
            break;
        
        case PSIDE_DOWN : 
            return (sfVector2i){0 , 1};
            break;
        
        case PSIDE_LEFT : 
            return (sfVector2i){-1 , 0};
            break;
        case PSIDE_UP : 
            return (sfVector2i){0 , -1};
            break;
    }
}


static void T_make_array_from_copy_(T_PiecesData dest , const T_PiecesData copy) {
    
    for(int i = 0 ; i < T_PIECES_SIZE ; i++) {
        dest[i] = copy[i];
    }

}



T_Piece* T_Piece_Create(T_PieceType piece_type) {
    
    T_Piece* new_piece = malloc(sizeof(T_Piece));

    if(new_piece == NULL) return NULL;
    
    new_piece->orientation = T_RIGHT_ROTATION;
    
    new_piece->state = PS_FALLING;
    
    new_piece->type = piece_type;

    new_piece->position.x = 0;
    new_piece->position.y = 0;


    switch (piece_type)
    {
        case PT_I_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)I_PIECE);
            break;
    
        case PT_J_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)J_PIECE);
            break;

        case PT_L_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)L_PIECE);
            break;
        
        case PT_O_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)O_PIECE);
            break;
        
        case PT_S_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)S_PIECE);
            break;
        
        case PT_T_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)T_PIECE);
            break;
        
        case PT_Z_PIECE:
            T_make_array_from_copy_(new_piece->data , (T_PiecesData)Z_PIECE);
            break;
    }

    return new_piece;

}

void T_Piece_Destroy(T_Piece* piece) {
    free(piece);
}

T_PieceTransformResult T_Piece_TryRotation(T_Piece* piece , int positive , T_PieceGrid* grid) {
    
    int current_rotation = piece->orientation;

    int new_rotation = 0;

    new_rotation += positive >= 0 ? 1 : -1;
    
    if(new_rotation > T_UP_ROTATION) new_rotation = T_RIGHT_ROTATION;
    
    if(new_rotation < T_RIGHT_ROTATION) new_rotation = T_UP_ROTATION;

    T_PieceTransformResult transform_result;

    if( T_Piece_IsOutOfBounds(piece->position , new_rotation , piece , grid) || 
        T_Piece_IsOverlaping(piece->position , new_rotation , piece , grid) 
    ) {
        
        printf("(ROTATION) couldn't perform rotation !\n");
        transform_result.is_valid = 0;
        transform_result.new_state = T_GS_FALLING;    
        return transform_result;
    }
    
    printf("\t (ROTATION) rotatated with success , current rotation : %d \n" , new_rotation);
    piece->orientation = new_rotation;
    
    transform_result.is_valid = 1;
    transform_result.new_state = T_GS_FALLING;
    return transform_result;
}



T_PieceTransformResult T_Piece_TryTranslation(T_Piece* piece , T_PieceSide side , T_PieceGrid* grid) {
    
    sfVector2i old_position = piece->position;

    sfVector2i offset = T_Side_To_Offset(side);
    
    sfVector2i new_position;
    
    new_position.x = piece->position.x + offset.x;
    
    new_position.y = piece->position.y + offset.y;

    int is_lateral_translation = side == PSIDE_RIGHT || side == PSIDE_LEFT ? 1 : 0;

    T_PieceTransformResult transform_result = {.is_valid = 1 , .new_state = T_GS_FALLING};

    int invalid_transform = T_Piece_IsOutOfBounds(new_position , piece->orientation , piece , grid) || 
                            T_Piece_IsOverlaping(new_position , piece->orientation , piece , grid);
    
    
    if (is_lateral_translation && invalid_transform) {
        transform_result.is_valid = 0;
        transform_result.new_state = T_GS_FALLING;
        return transform_result;
    }

    if(!is_lateral_translation && invalid_transform) {
        transform_result.is_valid = 0;
        transform_result.new_state = T_GS_UPDATE;
        return transform_result;
    }
   

    printf("\ttranslation performed with success, position updated\n" 
                "\told : (%d , %d)\tnew(%d ; %d)\n\n"  , 
                old_position.x , old_position.y , new_position.x , new_position.y  
            );

    piece->position = new_position;
    
    return transform_result;
}   

int T_Piece_IsOverlaping(sfVector2i new_position , int new_rotation , const T_Piece* piece , const T_PieceGrid* grid) 
{
    for(int y_offset = 0 ; y_offset < T_PIECE_HEIGHT ; y_offset++) {
        for(int x_offset = 0 ; x_offset < T_PIECE_WIDTH; x_offset++ ) {
            
            int piece_token = piece->data[T_FLATTEN_DATA(x_offset , y_offset , piece->orientation)];
            int grid_token = grid->pieces[T_FLATTEN_DATA_2D(piece->position.x + x_offset , piece->position.y + y_offset)];

            if(piece_token && grid_token) {
                printf("\t[OVERLAP CHECK] OVERLAP \n");
                return 1;
            } 
        }
    } 

    printf("\t[OVERLAP CHECK] NO OVERLAP \n");

    return 0;
}

int T_Piece_IsOutOfBounds(sfVector2i new_position , int new_rotation , const T_Piece* piece , const T_PieceGrid* grid)
{
    int is_out_of_bounds = 0;

    // Check if the piece was out of the grid. //

    for(int x_offset = 0 ; x_offset < T_PIECE_WIDTH ; x_offset++) {
        
        for(int y_offset = 0; y_offset < T_PIECE_HEIGHT ; y_offset++) {

            if(
                new_position.x + x_offset >= 0 && new_position.x + x_offset <= GRID_WIDTH 
                && new_position.y + y_offset >= 0 && new_position.y + y_offset <= GRID_HEIGHT
            ) continue;
            
            int token = piece->data[T_FLATTEN_DATA(x_offset , y_offset , piece->orientation)];
            printf("(%d , %d) -> %d\n" , x_offset + new_position.x , y_offset + new_position.y , token);
            if(token == FILLED) {
                is_out_of_bounds = 1;
                break;
            } 
                
        }

        if(is_out_of_bounds) {
            printf("\t[After check] Out of bounds !\n");
            return 1;
        } 
    }

    if(!is_out_of_bounds) {
        printf("\t[After check] Not out of bounds ! \n");
        return 0;
    }
}



void T_ShowPieces(const T_PiecesData pieces) {
    
    for(int orientation = 0 ; orientation < T_PIECE_ROTATIONS ; orientation++) {
        
        printf("\n\n");

        for(int y = 0 ; y < T_PIECE_WIDTH ; y++)
        {
            for(int x = 0 ; x < T_PIECE_HEIGHT ; x++)
            {
                printf(" %d | " , pieces[ T_FLATTEN_DATA(x , y , orientation ) ]);
            }
            
            printf("\n");
        }
    }

    printf("\n-------------------------------------------------------\n\n\n");

}
