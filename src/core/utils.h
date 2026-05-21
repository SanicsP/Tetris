#ifndef __INCLUDE_UTILS_H__
#define __INCLUDE_UTILS_H__

#include <CSFML/Graphics.h>
#include <stdlib.h>
#include <time.h>

#define FLAT_2D(x , y , w) (x) + (y)*w
#define FLAT_3D(x , y , z , w , h) (x) + (y)*w + (z)*w*h  

#define VEC2I_ADD(u , v)  (sfVector2i){u.x + v.x , u.y + v.y}
#define VEC2I_MULT(u , s)  (sfVector2i){u.x*s , u.y*s}

#define VEC2F_ADD(u , v)  (sfVector2f){u.x + v.x , u.y + v.y}
#define VEC2F_MULT(u , s)  (sfVector2f){u.x*s , u.y*s}


sfColor get_random_color();

#endif