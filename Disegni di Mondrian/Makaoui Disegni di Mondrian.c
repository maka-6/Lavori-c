/*
 * Nome: Disegni di Mondrian
 * Autore: Youness Makaoui
 * Luogo: Home
 * Data: 14/12/2023
 * Descrizione:
        - il programma controlla autenticità di un quadro di Mondrian
 */

#include <stdio.h>

#define DIM 50

typedef struct{

    int x;
    int y;

}Segment;

// inizializza il alto del quadrato e il numero di segmenti
FILE* sizeSegment( int* N, int* L,  char fileName[] ){

    FILE* pfile = fopen( fileName, "r" );

    if( pfile != NULL ){

        if ( fgetc( pfile ) != EOF ) {

            fscanf( pfile, "%d %d", N, L );

        } else {

            printf("\nErrore, file vuoto/illeggibile");
        }

        return pfile;

    } else {

        printf("\nErrore, file non trovato/inesistente");
    }

    return NULL;
}

void Load( Segment* A, Segment* B, FILE* pfile, int N ){

    for (int i = 0; i < N; i++) {

        // Inserimento dei dati per ogni segmento dal file
        fscanf( pfile, "%d %d %d %d", &A[i].x, &A[i].y, &B[i].x, &B[i].y );
    }

    fclose( pfile );
}

int main(){

    // numero di segmenti
    int N;
    // misura del alto del quadrato
    int L;

    // nome del file
    char fileName[DIM];

    printf("\nInserisci il nome del file es file.txt:\n->");
    scanf("%s",fileName);
    fflush(stdin);

    // file
    FILE* pfile = sizeSegment( &N, &L, fileName );

    if ( pfile != NULL ){

        if ( N > 0 && L > 0 ){

            Segment A[L];
            Segment B[L];

            Load( A, B, pfile, N );


        } else {

            printf("\ndati non validi");
        }
    }

    return (0);
}