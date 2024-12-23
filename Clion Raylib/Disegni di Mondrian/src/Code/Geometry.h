
#ifndef MAKAOUI_DISEGNI_DI_MONDRIAN_C_GEOMETRY_H
#define MAKAOUI_DISEGNI_DI_MONDRIAN_C_GEOMETRY_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include "raylib.h"

// punto
struct Dot{
    int x;
    int y;
};

typedef struct {
    struct Dot A;
    struct Dot B;
}Segment;

//
typedef struct {
    int nSeg;
    int lSquare;
    struct Dot *A;
    struct Dot *B;
}Mondrian;

//
typedef struct Payload{
    int number;
    Mondrian *segment;
    struct Payload *left;
    struct Payload *right;
}Tree;

typedef struct {
    struct Dot *start; // Array di punti iniziali
    struct Dot *end;   // Array di punti finali
    int count;         // Numero di segmenti
} SegmentList;

typedef struct {
    SegmentList horizontal; // Lista di segmenti orizzontali
    SegmentList vertical;   // Lista di segmenti verticali
} MondrianSegments;

// centro dello schermo
struct Dot center( int screenHeight, int screenWidth ){
    struct Dot cent;
    cent.x = screenWidth / 2;
    cent.y = screenHeight / 2;
    return cent;
}

// distanza tra due punti
int distance( struct Dot a, struct Dot b ){
    double tmp;
    tmp=pow(a.x-b.x,2);
    tmp+=pow(a.y-b.y,2);
    return (int)sqrt(tmp);
}

#endif //MAKAOUI_DISEGNI_DI_MONDRIAN_C_GEOMETRY_H