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
#include "Code/Check_mondrian.c"

// legge la prima riga del file per il lato del quadrato e numero segmenti
FILE* sizeSegment( struct Mondrian *paint ){

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

    exit(5);
}

// carica i dati nel file in due segmenti
int Load( Segments segment, FILE *pointFile, struct Mondrian Paint ){

    int i;

    for (i = 0; i < Paint.nSeg; i++) {

        // Inserimento dei dati per ogni segmento dal file
        fscanf(pointFile, "%d %d %d %d", &segment.A[i].x, &segment.A[i].y, &segment.B[i].x, &segment.B[i].y );

    }

    for (i = 0; i < Paint.nSeg; ++i) {

        if (( segment.A[i].x > Paint.lSquare || segment.A[i].x < 0 )||( segment.A[i].y > Paint.lSquare || segment.A[i].y < 0 )){

            if (( segment.B[i].x > Paint.lSquare || segment.B[i].x < 0 )||( segment.B[i].y > Paint.lSquare || segment.B[i].y < 0 )){
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

    // numero di segmenti
    // misura del alto del quadrato

    struct Mondrian Paint;

    // il file
    FILE* pointFile = sizeSegment( &Paint );

    if ( Paint.nSeg > 1 && Paint.lSquare > 1 ){

        Segments segment;
        segment.A = (struct Dot*) malloc(Paint.nSeg * sizeof(struct Dot));
        segment.B = (struct Dot*) malloc(Paint.nSeg * sizeof(struct Dot));

        int check = Load( segment, pointFile, Paint );

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

        struct Dot cent = center( screen.height, screen.width );

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