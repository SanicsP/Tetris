#include <tetris_tests.h>
#include <string.h>

int tetris_unit_tests() {
    
    T_PieceGrid* test_grid = T_PieceGrid_Create();

    assert(test_grid);
    
    T_Piece_Destroy(test_grid->failling_piece);

    test_grid->failling_piece = T_Piece_Create(PT_J_PIECE);
    
    if(test_grid->failling_piece == NULL) return 0;

    T_ShowPieces(test_grid->failling_piece->data);

    // Should be false because the piece spawned in the high-left corner
    
    printf("Testing T_PieceTryTranslation() with PSIDE_LEFT ...\n");

    assert(T_Piece_TryTranslation(test_grid->failling_piece , PSIDE_LEFT , test_grid).is_valid);
    assert(!T_Piece_TryTranslation(test_grid->failling_piece , PSIDE_LEFT , test_grid).is_valid);

    
    printf("Testing T_PieceTryTranslation() with PSIDE_RIGHT ...\n");

    assert(T_Piece_TryTranslation(test_grid->failling_piece , PSIDE_RIGHT , test_grid).is_valid);

    
    printf("Test loop T_PieceTryTranslation() with PSIDE_DOWN 60 Times \n");

    int n_down = 0;

    for(int i = 0 ; i < 60 ; i++) {
        if(!T_Piece_TryTranslation(test_grid->failling_piece , PSIDE_DOWN , test_grid).is_valid) break;
        n_down++;
    }

    assert(n_down == GRID_HEIGHT - 1);

    printf("Testing Iteration finished , T_Piece_TryTranslation its fine \n\n");


    printf("Testing T_Piece_Rotate()\n");
    
    assert(T_Piece_TryRotation(test_grid->failling_piece , T_POSITIVE , test_grid).is_valid);

    printf("T_Piece_Rotate() its fine\n");


    T_PieceGrid_Destroy(test_grid);

    printf("\n\n Unit tests completed , everything is fine\n");

    

}
