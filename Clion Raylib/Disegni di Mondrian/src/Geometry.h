
#ifndef MAKAOUI_DISEGNI_DI_MONDRIAN_C_GEOMETRY_H
#define MAKAOUI_DISEGNI_DI_MONDRIAN_C_GEOMETRY_H

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "raylib.h"

#define DIM 16

typedef struct{

    int x;
    int y;

} Dot;

int distance( Dot a, Dot b ){

    double tmp;
    tmp=pow(a.x-b.x,2);
    tmp+=pow(a.y-b.y,2);
    return (int)sqrt(tmp);
}

Dot center( int screenHeight, int screenWidth ){

    Dot cen;

    cen.x = screenWidth / 2;
    cen.y = screenHeight / 2;

    return cen;
}

typedef struct{

    int height;
    int width;

}Screen;

Screen screen;

#endif //MAKAOUI_DISEGNI_DI_MONDRIAN_C_GEOMETRY_H