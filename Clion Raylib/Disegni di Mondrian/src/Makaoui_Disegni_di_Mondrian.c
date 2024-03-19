/*
    * Nome: Disegni di Mondrian
    * Autore: Youness Makaoui
    * Luogo: Home
    * Data: 14/12/2023
    * Descrizione:
        - il programma controlla autenticità di un quadro di Mondrian
 */

#include "Code/Geometry.h"
#include "Code/paint_square.c"

// legge la prima riga del file per il lato del quadrato e numero segmenti
FILE* sizeSegment( struct Mondrian *paint ){

    FILE* pointFile = fopen("Data/disegno.txt", "r" );

    int check = getc( pointFile );

    if( pointFile != NULL ){

        if ( check != EOF ) {

            // riposiziono il cursore all'inizio del file
            ungetc(check, pointFile);

            fscanf(pointFile, "%d %d", &paint->nSeg, &paint->lSquare );

            if ( paint->nSeg == 0 || paint->lSquare == 0 ){

                return NULL;
            }
        }

        return pointFile;
    }

    exit(5);
}

// carica i dati nel file in due segmenti
int Load( Dot *A, Dot *B, FILE *pointFile, struct Mondrian Paint ){

    int i;

    for (i = 0; i < Paint.nSeg; i++) {

        // Inserimento dei dati per ogni segmento dal file
        fscanf(pointFile, "%d %d %d %d", &A[i].x, &A[i].y, &B[i].x, &B[i].y );

    }

    for (i = 0; i < Paint.nSeg; ++i) {

        if (( A[i].x > Paint.lSquare || A[i].x < 0 )||( A[i].y > Paint.lSquare || A[i].y < 0 )||( B[i].x > Paint.lSquare || B[i].x < 0 )||( B[i].y > Paint.lSquare || B[i].y < 0 )){

            return 0;
        }
    }

    return 1;
}

int main(){

    printf("\n                [ !!ATTENZIONE!! ]"
                  "\n[ il File di testo deve rispettare un preciso formato ]");
    printf("\n-------------------------------------------------------\n"
                  "         [ cercare esempio.txt in ./src/Data ]\n");

    // numero di segmenti
    // misura del alto del quadrato

    struct Mondrian Paint;

    // il file
    FILE* pointFile = sizeSegment( &Paint );

    if ( Paint.nSeg > 1 && Paint.lSquare > 1 ){

        Dot A[Paint.nSeg];
        Dot B[Paint.nSeg];

        int check = Load( A, B, pointFile, Paint );

        // chiudo il file
        fclose(pointFile );

        if ( check == 0 ){

            // esco se i dati sono illeggibili o errati
            printf("\nERRORE, File illeggibile o Dati non Validi");
            printf("\n------------------------------------------\n"
                          "            Riavviare e riprovare\n");
            return 0;
        }

        printf("\nLettura avvenuta correttamente\n");

        // inizializzo la finestra
        InitWindow(screen.width, screen.height, "Mostra su Mondrian");
        screen.width = GetScreenWidth();
        screen.height = GetScreenHeight();

        Dot cent = center( screen.height, screen.width );

        // imposto un target di fps
        SetTargetFPS(144);

        Texture2D texture = LoadTexture("texture/paint_background.png");

        while (!WindowShouldClose()){

            BeginDrawing();
            paint( (Paint.lSquare+18)*10, cent, texture );
            EndDrawing();

        }
        // chiudo la finestra
        CloseWindow();

    } else {
        // esco se i dati sono errati
        printf("\nERRORE, Dati non Validi");
        printf("\n------------------------\n"
               "Riavviare e riprovare");
    }

    return (0);
}