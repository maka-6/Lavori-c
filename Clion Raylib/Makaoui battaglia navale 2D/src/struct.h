//
// Created by makao on 21/01/2024.
//

#ifndef BATTAGLIA_NAVALE_C_STRUCT_H
#define BATTAGLIA_NAVALE_C_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#define r 23
#define c 23

// struct nave
typedef struct{

    int dim;// dimensione della nave

    // coordinate della nave
    int x;
    int y;

    int verso;// verso della nave

}oggetto;


// struct matrice
typedef struct tab{

    char campo[r][c];

    char cont[r][c]; // matrice indici navi

    int nv; // numero navi rimaste

    struct tab *pnext;

}tab;


// stampa resoconto partita nel file
typedef struct part{

    char vincitore[r]; // nome del vincitore

    int nvG; // numero navi giocatore rimaste

    int nvC; // numero navi cpu rimaste

    struct part *pnext;

}part;

#endif //BATTAGLIA_NAVALE_C_STRUCT_H