/*
    * Nome: check mondrian
    * Autore: Youness Makaoui
    * Luogo: Home
    * Data: 20/03/2024
    * Descrizione:
        - verifica i segmenti del quadro
*/

#include "Geometry.h"

typedef struct {
    struct Dot *start; // Array di punti iniziali
    struct Dot *end;   // Array di punti finali
    int count;         // Numero di segmenti
} SegmentList;

typedef struct {
    SegmentList horizontal; // Lista di segmenti orizzontali
    SegmentList vertical;   // Lista di segmenti verticali
} MondrianSegments;

MondrianSegments separateSegments(Mondrian *segments);

// Prototipo della funzione per trovare o costruire un segmento principale
Segment MainSegmentBuild(SegmentList segmentList, int segmentLength, int isHorizontal);

int checkSeg( Mondrian *segments ){

    MondrianSegments separate = separateSegments(segments);
    Segment mainHorizontal;
    Segment mainVertical;
    //Tree *root;
    //
    int i;
    for (i = 0; i < separate.horizontal.count; ++i) {
        if (distance(separate.horizontal.start[i],separate.horizontal.end[i])==segments->lSquare){
            mainHorizontal.A = separate.horizontal.start[i];
            mainHorizontal.B = separate.horizontal.end[i];
            break;
        }
    }
    for (i = 0; i < separate.vertical.count; ++i) {
        if (distance(separate.vertical.start[i],separate.vertical.end[i])==segments->lSquare){
            mainVertical.A = separate.vertical.start[i];
            mainVertical.B = separate.vertical.end[i];
            break;
        }
    }

    // Trova o costruisci il segmento orizzontale principale
    mainHorizontal = MainSegmentBuild(separate.horizontal, segments->lSquare, 1);

    // Trova o costruisci il segmento verticale principale
    mainVertical = MainSegmentBuild(separate.vertical, segments->lSquare, 0);

    // Libera la memoria allocata
    free(separate.vertical.start);
    free(separate.vertical.end);
    free(separate.horizontal.start);
    free(separate.horizontal.end);
    return 1;
}

MondrianSegments separateSegments(Mondrian *segments){
    MondrianSegments separate = {0}; // Inizializza tutti i puntatori a NULL
    separate.vertical.count = 0;
    separate.horizontal.count = 0;
    separate.horizontal.start = (struct Dot*) malloc(segments->nSeg / 2 * sizeof(struct Dot));
    separate.horizontal.end = (struct Dot*) malloc(segments->nSeg / 2 * sizeof(struct Dot));
    separate.vertical.start = (struct Dot*) malloc(segments->nSeg / 2 * sizeof(struct Dot));
    separate.vertical.end = (struct Dot*) malloc(segments->nSeg / 2 * sizeof(struct Dot));

    // Controlla allocazioni
    if (!separate.horizontal.start || !separate.horizontal.end ||
        !separate.vertical.start || !separate.vertical.end) {
        printf("Errore: memoria insufficiente per separare i segmenti.\n");

        // Libera la memoria già allocata
        free(separate.horizontal.start);
        free(separate.horizontal.end);
        free(separate.vertical.start);
        free(separate.vertical.end);
        exit(1); // Termina con errore
    }
    int i;
    for (i = 0; i < segments->nSeg; ++i) {
        if ( segments->A[i].x == segments->B[i].x ){
            separate.horizontal.start[separate.horizontal.count] = segments->A[i];
            separate.horizontal.end[separate.horizontal.count] = segments->B[i];
            separate.horizontal.count++;

        } else if ( segments->A[i].y == segments->B[i].y ){
            separate.vertical.start[separate.vertical.count] = segments->A[i];
            separate.vertical.end[separate.vertical.count] = segments->B[i];
            separate.vertical.count++;
        }
    }
    return separate;
}

// Prototipo della funzione per trovare o costruire un segmento principale
Segment MainSegmentBuild(SegmentList segmentList, int segmentLength, int isHorizontal){
    Segment mainSegment = {0};



    return mainSegment;
}