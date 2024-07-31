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

        // controllo che il file abbia contenuto
        if ( feof(pointFile) != EOF ) {
            // controllo che i dati presi siano 2
            if ( fscanf(pointFile, "%d %d", &paint->nSeg, &paint->lSquare ) != 2 )
                return NULL;
        }
        return pointFile;
    }
    printf("\nOut of memory");
    exit(5);
}

// carica i dati nel file in due segmenti
int LoadData(Mondrian *paint, FILE *pointFile ){

    int i;

    for (i = 0; i < paint->nSeg; i++) {
        // Inserimento dei dati per ogni segmento dal file
        if (fscanf(pointFile, "%d %d %d %d", &paint->A[i].x, &paint->A[i].y, &paint->B[i].x, &paint->B[i].y ) != 4 )
            return 0;
    }

    for (i = 0; i < paint->nSeg; ++i) {

        if ((paint->A[i].x > paint->lSquare || paint->A[i].x < 0 ) || (paint->A[i].y > paint->lSquare || paint->A[i].y < 0 )){

            if ((paint->B[i].x > paint->lSquare || paint->B[i].x < 0 ) || (paint->B[i].y > paint->lSquare || paint->B[i].y < 0 )){
                return 1;
            }
            return 1;
        }
    }
    return 0;
}

int main(){

    printf("\n                [ !!ATTENZIONE!! ]"
                  "\n[ il File di testo deve rispettare un preciso formato ]");
    printf("\n-------------------------------------------------------\n"
                  "         [ cercare esempio.txt in ./src/Data ]\n");

    //
    Mondrian *paint;
    paint = (Mondrian*) malloc(sizeof(Mondrian));
    //
    if ( paint == NULL ){
        printf("\nOut of memory");
        return 0;
    }
    // il file dati
    FILE* pointFile = sizeSegment( paint );

    if ( pointFile == NULL ){
        printf("\nFile Illeggibile");
        return 0;
    }
    // controllo che i valori siano validi
    if (paint->nSeg > 1 && paint->lSquare > 1 ){

        // alloco memoria
        paint->A = (struct Dot*) malloc(paint->nSeg * sizeof(struct Dot));
        paint->B = (struct Dot*) malloc(paint->nSeg * sizeof(struct Dot));

        // controllo se l'allocazione è avvenuta correttamente
        if (paint->A == NULL || paint->B == NULL ){
            printf("\nOut of memory");
            // chiudo il file
            fclose(pointFile );
            return 5;
        }

        // controllo che il quadro è autentico
        if ( LoadData(paint, pointFile) + checkSeg(paint ) == 0 ){
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

        // buon fine
        printf("\nLettura avvenuta correttamente\n");

        int screenWidth, screenHeight;
        // inizializzo la finestra
        InitWindow(GetScreenWidth(), GetScreenHeight(), "Mostra su Mondrian");
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        struct Dot cent = center( screenHeight, screenWidth );

        // imposto un target di fps
        SetTargetFPS(114);

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