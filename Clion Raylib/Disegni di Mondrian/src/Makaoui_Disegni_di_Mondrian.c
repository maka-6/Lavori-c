/*
 * Nome: Disegni di Mondrian
 * Autore: Youness Makaoui
 * Luogo: Home
 * Data: 14/12/2023
 * Descrizione:
        - il programma controlla autenticità di un quadro di Mondrian
 */

#include <stdio.h>
#include "raylib.h"

#define DIM 50

typedef struct{

    int x;
    int y;

}Segment;

// inizializza il alto del quadrato e il numero di segmenti
FILE* sizeSegment( int *N, int *L,  char fileName[] ){

    FILE* pointFile = fopen(fileName, "r" );

    char check = fgetc( pointFile );

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

void Load( Segment* A, Segment* B, FILE* pointFile, int N ){

    for (int i = 0; i < N; i++) {
        // Inserimento dei dati per ogni segmento dal file
        fscanf(pointFile, "%d %d %d %d", &A[i].x, &A[i].y, &B[i].x, &B[i].y );
    }

    fclose(pointFile );
}

int main(){

    // numero di segmenti
    int N;
    // misura del alto del quadrato
    int L;

    // nome del file
    char fileName[DIM];

    printf("\nATTENZIONE, il file deve rispettare un preciso formato altrimenti il programma restituirà errore");
    printf("\nL'esempio si trova in 'esempio.txt'");
    printf("\nInserisci il nome del file es file.txt:\n->");
    scanf("%s",fileName);
    fflush(stdin);

    // il file
    FILE* pointFile = sizeSegment( &N, &L, fileName );

    if ( pointFile != NULL ){

        if ( N > 0 && L > 0 ){

            Segment A[N];
            Segment B[N];

            Load(A, B, pointFile, N );

            printf("\n%2d %2d",N, L);

            for (int i = 0; i < N; ++i) {

                printf("\n%-2d %-2d %-2d %-2d\n", A[i].x, A[i].y, B[i].x, B[i].y);
            }


        } else {

            printf("\nERRORE, File illeggibile o Dati non Validi");
        }

        // chiudo il file
        fclose( pointFile );

    } else {

        printf("ERRORE, File non trovato");
    }

    InitWindow( 800, 400, "Mondrian");

    while (!WindowShouldClose()){

        BeginDrawing();
        DrawCircle( 70, 70, 70, RED);
        EndDrawing();
    }

    CloseWindow();

    return (0);
}