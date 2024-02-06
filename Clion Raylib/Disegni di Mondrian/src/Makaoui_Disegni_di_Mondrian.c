/*
 * Nome: Disegni di Mondrian
 * Autore: Youness Makaoui
 * Luogo: Home
 * Data: 14/12/2023
 * Descrizione:
        - il programma controlla autenticità di un quadro di Mondrian
 */

#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define DIM 50

typedef struct{

    int x;
    int y;

}Segment;

// legge la prima riga del file per il lato del quadrato e numero segmenti
FILE* sizeSegment( int *N, int *L,  char *fileName ){

    FILE* pointFile = fopen(fileName, "r" );

    int check = getc( pointFile );

    if( pointFile != NULL ){

        if ( check != EOF ) {

            // riposiziono il cursore all'inizio del file
            ungetc(check, pointFile);

            fscanf(pointFile, "%d %d", N, L );

            if ( N == 0 || L == 0 ){

                return NULL;
            }
        }

        return pointFile;
    }

    return NULL;
}

// carica i dati nel file in due segmenti
int Load( Segment *A, Segment *B, FILE *pointFile, int N, int L ){

    int i;

    for (i = 0; i < N; i++) {
        // Inserimento dei dati per ogni segmento dal file

        fscanf(pointFile, "%d %d %d %d", &A[i].x, &A[i].y, &B[i].x, &B[i].y );

    }

    for (i = 0; i < N; ++i) {

        if (( A[i].x > L || A[i].x < 0 )||( A[i].y > L || A[i].y < 0 )||( B[i].x > L || B[i].x < 0 )||( B[i].y > L || B[i].y < 0 )){

            // chiudo il file
            fclose(pointFile );
            return 0;
        }
    }

    // chiudo il file
    fclose(pointFile );

    return 1;
}

void frame( int screenWidth, int screenHeight, int lSquare );

int main(){

    // nome del file
    char fileName[DIM] = "disegno.txt";

    printf("\n\t[ !!ATTENZIONE!! ]"
           "\n[ il File deve rispettare un preciso formato ]");
    printf("\n-------------------------------------\n"
           "[ cercare esempio.txt in ./src/ ]");

    // numero di segmenti
    int nSegment;
    // misura del alto del quadrato
    int lSquare;

    // il file
    FILE* pointFile = sizeSegment(&nSegment, &lSquare, fileName );

    if ( pointFile != NULL ){

        if (nSegment > 0 && lSquare > 0 ){

            Segment A[nSegment];
            Segment B[nSegment];

            int check = Load(A, B, pointFile, nSegment, lSquare );

            if ( check == 0 ){

                // esco se i dati sono illeggibili o errati
                printf("\nERRORE, File illeggibile o Dati non Validi");
                printf("\n------------------------------------------\n"
                       "Riavviare e riprovare\n");
                return 0;
            }

            printf("\nLettura avvenuta correttamente\n");

            // ciao
            InitWindow( GetScreenWidth(), GetScreenHeight(), "Mostra su Mondrian");

            //
            SetTargetFPS(120);

            while (!WindowShouldClose()){

                frame( GetScreenWidth(), GetScreenHeight(), lSquare*20 );
            }

            CloseWindow();

        } else {

            // esco se i dati sono errati
            printf("\nERRORE, Dati non Validi");
            printf("\n------------------------\n"
                   "Riavviare e riprovare");
        }

    } else {

        // esco se non trovo nessun file
        printf("\nERRORE, File non trovato");
        printf("\n-------------------------\n"
               "Riavviare e riprovare\n");
    }

    return (0);
}

// lavora sul frame er renderizzare il quadro
void frame( int screenWidth, int screenHeight, int lSquare ){

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText( "Quadro di Piet Mondrian:",  (screenWidth/3) - lSquare/2, (screenHeight / 3) - lSquare/2, 40, BLACK);
    DrawRectangle( (screenWidth / 2) - (lSquare/2), (screenHeight / 2) - (lSquare/2), lSquare/1, lSquare/1, RED );
    DrawRectangle( (screenWidth / 2) - (lSquare/2), (screenHeight / 2) - (lSquare/2), lSquare/2, lSquare/2, BLACK);
    DrawRectangle( 20, 30, 100, 100, BLACK);
    EndDrawing();

}