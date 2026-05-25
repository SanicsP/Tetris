
#include "utils.h"


sfColor get_random_color() 
{
    srand(time(NULL));

    int color_id = rand() % 4;
    
    switch (color_id) {
        case 0 : 
            return sfColor_fromInteger(0x0341AEFF);

        case 1 : 
            return sfColor_fromInteger(0x72CB3BFF);


        case 2 : 
            return sfColor_fromInteger(0xFFD500FF);


        case 3 : 
            return sfColor_fromInteger(0xFF971CFF);

        
        case 4 : 
            return sfColor_fromInteger(0xFF3213FF);
    }
    
}

sfColor utils_get_color_by_type(int piece_type) {
    
    switch (piece_type)
    {
        case 0 : 
            return sfColor_fromInteger(0XEBF527FF);
        case 1 : 
            return sfColor_fromInteger(0X00FFD7FF);
        case 2 : 
            return sfColor_fromInteger(0X00FF4CFF);
        case 3 : 
            return sfColor_fromInteger(0XFF002BFF);
        case 4 : 
            return sfColor_fromInteger(0XFF8400FF);
        case 5 : 
            return sfColor_fromInteger(0X001EFFFF);
        case 6 : 
            return sfColor_fromInteger(0XFF00FBFF);
    }
}

