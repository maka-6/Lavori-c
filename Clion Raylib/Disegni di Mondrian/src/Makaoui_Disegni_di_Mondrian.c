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
#include "Code/Check_segments.c"

// legge la prima riga del file per il lato del quadrato e numero segmenti
FILE* sizeSegment( Mondrian *paint ){

    FILE* pointFile = fopen("Data/disegno.txt", "r" );
    if( pointFile != NULL ){

        if ( feof(pointFile) != EOF ) {

            fscanf(pointFile, "%d %d", &paint->nSeg, &paint->lSquare );

            if ( paint->nSeg == 0 || paint->lSquare == 0 ){
                return NULL;
            }
        }
        return pointFile;
    }
    printf("\nOut of memory");
    exit(5);
}

// carica i dati nel file in due segmenti
int Load( Mondrian *Paint, FILE *pointFile ){

    int i;

    for (i = 0; i < Paint->nSeg; i++) {
        // Inserimento dei dati per ogni segmento dal file
        fscanf(pointFile, "%d %d %d %d", &Paint->A[i].x, &Paint->A[i].y, &Paint->B[i].x, &Paint->B[i].y );
    }

    for (i = 0; i < Paint->nSeg; ++i) {

        if (( Paint->A[i].x > Paint->lSquare || Paint->A[i].x < 0 )||( Paint->A[i].y > Paint->lSquare || Paint->A[i].y < 0 )){

            if (( Paint->B[i].x > Paint->lSquare || Paint->B[i].x < 0 )||( Paint->B[i].y > Paint->lSquare || Paint->B[i].y < 0 )){
                return 0;
            }
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

    Mondrian *paint;
    paint = (Mondrian*) malloc(sizeof(Mondrian));
    if ( paint == NULL ){
        printf("\nOut of memory");
        return 0;
    }
    // il file
    FILE* pointFile = sizeSegment( paint );

    if (paint->nSeg > 1 && paint->lSquare > 1 ){

        paint->A = (struct Dot*) malloc(paint->nSeg * sizeof(struct Dot));
        paint->B = (struct Dot*) malloc(paint->nSeg * sizeof(struct Dot));

        if (paint->A == NULL || paint->B == NULL ){

            printf("\nOut of memory");
            // chiudo il file
            fclose(pointFile );
            return 5;
        }
        int check = Load(paint, pointFile );

        if ( check == 0 ){
            // esco se i dati sono illeggibili o errati
            printf("\nERRORE, File illeggibile o Dati non Validi");
            printf("\n------------------------------------------\n"
                          "            Riavviare e riprovare\n");

            // Libera la memoria allocata per i segmenti
            free(paint->A);
            free(paint->B);
            // chiudo il file
            fclose(pointFile );
            return 0;
        }
        printf("\nLettura avvenuta correttamente\n");

        checkSeg(paint );

        int screenWidth = GetScreenWidth(), screenHeight = GetScreenHeight();
        // inizializzo la finestra
        InitWindow(screenWidth, screenHeight, "Mostra su Mondrian");
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        struct Dot cent = center( screenHeight, screenWidth );

        // imposto un target di fps
        SetTargetFPS(144);

        Texture2D texture = LoadTexture("texture/paint_background.png");

        while (!WindowShouldClose()){
            BeginDrawing();
            draw((paint->lSquare + 18) * 10, cent, texture );
            EndDrawing();
        }
        // chiudo la finestra
        CloseWindow();
        // Libera la memoria allocata per i segmenti
        free(paint->A);
        free(paint->B);

    } else {
        // esco se i dati sono errati
        printf("\nERRORE, Dati non Validi");
        printf("\n------------------------\n"
               "Riavviare e riprovare");
    }
    // chiudo il file
    fclose(pointFile );
    free(paint);
    return 0;
}